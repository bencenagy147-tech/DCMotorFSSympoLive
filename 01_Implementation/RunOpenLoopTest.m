%% RunOpenLoopTest - deploy DCMotorOpenLoop to the Arduino Uno and log data
% Builds, downloads and runs the open-loop duty sequence in Monitor & Tune
% (External mode over serial). The run stops automatically after the stop
% time and the logged signals are saved to a .mat file in this folder.
% WARNING: the motor runs at up to +/-100 % duty. Clamp the motor first.
%
% Optional: define olRunCfg in the base workspace before running
%   olRunCfg.DutyGain = 0;              % 0 = motor not driven (hand-turn test)
%   olRunCfg.StopTime = 40;             % [s] override run length
%   olRunCfg.DataFile = 'HandTurnTestData.mat';

mdl = 'DCMotorOpenLoop';
DCMotorParams;
cfg = struct('DutyGain', OL_DutyGain, 'StopTime', OL_StopTime, ...
             'DataFile', 'OpenLoopTestData.mat');
if exist('olRunCfg', 'var')
    fn = fieldnames(olRunCfg);
    for k = 1:numel(fn), cfg.(fn{k}) = olRunCfg.(fn{k}); end
end

open_system(mdl);
set_param(mdl, 'SimulationMode', 'external');
% the model InitFcn re-runs DCMotorParams, so overrides go through the
% model workspace-independent base variables after InitFcn via StopTime/Gain
set_param(mdl, 'StopTime', num2str(cfg.StopTime));
set_param(mdl, 'InitFcn', sprintf('DCMotorParams; OL_DutyGain = %g;', cfg.DutyGain));

Simulink.sdi.clear;
set_param(mdl, 'SimulationCommand', 'start');   % build, load, connect, run

% wait until the target run finishes; record wall-clock vs. target time
timing = zeros(0, 2);
tWait = tic;
while ~strcmp(get_param(mdl, 'SimulationStatus'), 'stopped')
    pause(0.25);
    if strcmp(get_param(mdl, 'SimulationStatus'), 'running')
        timing(end+1, :) = [toc(tWait), get_param(mdl, 'SimulationTime')]; %#ok<SAGROW>
    end
    if toc(tWait) > 900
        set_param(mdl, 'SimulationCommand', 'stop');
        error('RunOpenLoopTest:Timeout', 'Run did not finish within 15 min.');
    end
end

% restore the saved model settings
set_param(mdl, 'StopTime', 'OL_StopTime', 'InitFcn', 'DCMotorParams;');
save_system(mdl);

% real-time factor: wall-clock seconds per target (model) second
valid = timing(:, 2) > 1;
if nnz(valid) > 4
    pf = polyfit(timing(valid, 2), timing(valid, 1), 1);
    realTimeFactor = pf(1);
else
    realTimeFactor = NaN;
end

% collect the logged signals from the Simulation Data Inspector
runIDs = Simulink.sdi.getAllRunIDs;
olRun  = Simulink.sdi.getRun(runIDs(end));
olData = struct();
for k = 1:olRun.SignalCount
    sig = olRun.getSignalByIndex(k);
    olData.(matlab.lang.makeValidName(sig.Name)) = sig.Values;
end
olInfo.Date           = datetime('now');
olInfo.Ts             = Ts;
olInfo.SeqTime        = OL_SeqTime;
olInfo.SeqDuty        = OL_SeqDuty;
olInfo.DutyGain       = cfg.DutyGain;
olInfo.Supply_V       = Motor_SupplyVoltage;
olInfo.Timing         = timing;
olInfo.RealTimeFactor = realTimeFactor;

dataFile = fullfile(fileparts(mfilename('fullpath')), cfg.DataFile);
save(dataFile, 'olData', 'olInfo');
fprintf('Data saved to %s (%d signals), real-time factor %.3f\n', ...
        dataFile, olRun.SignalCount, realTimeFactor);
