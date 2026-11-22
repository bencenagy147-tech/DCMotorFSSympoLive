%% IdentifyMotorPlant - identify duty[%] -> speed[rpm] plant from M1 open-loop data
% Uses OpenLoopTestData_Run1.mat (logged before the rpm calibration block was
% added), applies the calibration divisor offline, then fits process models.
% Estimation: positive-duty half (0..11 s); validation: negative half (11..23 s).
% Output: MotorPlantModel.mat (01_Implementation) and figures in 02_SupportingArtifacts.

DCMotorParams;
here    = fileparts(mfilename('fullpath'));
artDir  = fullfile(here, '..', '02_SupportingArtifacts');
S       = load(fullfile(here, 'OpenLoopTestData_Run1.mat'));

u = double(S.olData.Duty_pct.Data(:));
y = double(S.olData.Speed_rpm.Data(:)) / Spd_CalDivisor;   % calibrated rpm
t = S.olData.Speed_rpm.Time(:);

data = iddata(y, u, Ts, 'InputName', 'Duty', 'InputUnit', '%', ...
              'OutputName', 'Speed', 'OutputUnit', 'rpm');
data.InterSample = 'zoh';                 % PWM duty is piecewise constant
ze = data(t < 11);
zv = data(t >= 11);

%% Delay first (includes the 50 ms counting window of EncoderSpeed)
nk = delayest(ze, 1, 1, 0, 20);
fprintf('delayest: nk = %d samples (%.0f ms)\n', nk, 1000*nk*Ts);

%% Process models (step data -> procest), delay hedged by the free Td
opt = procestOptions('Focus', 'simulation', 'DisturbanceModel', 'none');
mP1D = procest(ze, 'P1D', opt);
mP2D = procest(ze, 'P2D', opt);
mP1  = procest(ze, 'P1',  opt);
[~, fits] = compare(zv, mP1, mP1D, mP2D);
fprintf('Validation fit (neg. half): P1 %.1f%%, P1D %.1f%%, P2D %.1f%%\n', fits{:});
fitsAll = cell2mat(fits);

%% Residuals of the P1D model
[~, r] = resid(zv, mP1D);
N = size(zv.y, 1); conf99 = 2.58/sqrt(N);
xcf = r(:,2,1) / sqrt(r(1,1,1)*r(1,2,2));
fprintf('P1D: input-residual correlation within 99%% bound: %s\n', string(all(abs(xcf) < conf99)));

%% Results
Plant_K   = mP1D.Kp;          % [rpm/%]
Plant_Tau = mP1D.Tp1;         % [s]
Plant_Td  = mP1D.Td;          % [s]
fprintf('\nP1D: K = %.3f rpm/%%, Tau = %.4f s, Td = %.4f s\n', Plant_K, Plant_Tau, Plant_Td);
fprintf('P2D: K = %.3f rpm/%%, Tp1 = %.4f s, Tp2 = %.4f s, Td = %.4f s\n', ...
        mP2D.Kp, mP2D.Tp1, mP2D.Tp2, mP2D.Td);

% static gain per direction from steady states (last 40 % of each segment)
T = S.olInfo.SeqTime; D = S.olInfo.SeqDuty; ss = nan(1, numel(T)-1);
for i = 1:numel(T)-1
    idx = t >= T(i) + 0.6*(T(i+1)-T(i)) & t < T(i+1);
    ss(i) = mean(y(idx));
end
staticTbl = table(D(1:end-1)', ss', 'VariableNames', {'Duty_pct', 'Speed_rpm'});
disp(staticTbl);

save(fullfile(here, 'MotorPlantModel.mat'), 'mP1', 'mP1D', 'mP2D', 'fitsAll', ...
     'Plant_K', 'Plant_Tau', 'Plant_Td', 'staticTbl');

%% Figures
f1 = figure('Visible', 'off', 'Position', [100 100 900 600]);
subplot(3,1,1); plot(t, u, 'LineWidth', 1.2); grid on; ylabel('Duty [%]');
title('M1 open-loop test (run 1), calibrated speed');
subplot(3,1,2); plot(t, y, 'LineWidth', 1.2); grid on; ylabel('Speed [rpm]');
yline([2200 -2200], '--', {'+2200', '-2200'});
subplot(3,1,3); plot(t, double(squeeze(S.olData.Sensor_V.Data)), 'LineWidth', 1.2); grid on;
ylabel('ACS712 [V]'); xlabel('Time [s]');
exportgraphics(f1, fullfile(artDir, 'M1_OpenLoop_Run1.png'));

f2 = figure('Visible', 'off', 'Position', [100 100 900 400]);
compare(zv, mP1, mP1D, mP2D); grid on;
title('Validation on negative-duty half (not used for estimation)');
exportgraphics(f2, fullfile(artDir, 'M1_PlantID_Validation.png'));
close([f1 f2]);
