%% ReportClosedLoop - plot and report the closed-loop hardware run
DCMotorParams;
root = currentProject().RootFolder;
S  = load(fullfile(root, '01_Implementation', 'ClosedLoopTestData.mat'));
t  = S.cl.Speed_rpm.Time;
w  = double(squeeze(S.cl.Speed_rpm.Data));
u  = double(squeeze(S.cl.Duty_pct.Data));
r  = interp1(Ref_Time, Ref_Values, t, 'previous', 'extrap');
e  = r - w;

fig = figure('Name', 'DC Motor PI Speed Control - Arduino Uno', 'Color', 'w', ...
             'Position', [80 80 1200 800]);
tl = tiledlayout(3, 1, 'TileSpacing', 'compact');
title(tl, 'Pololu 4841 PI speed control on Arduino Uno (hardware run)', 'FontWeight', 'bold');
nexttile; plot(t, r, 'k--', 'LineWidth', 1.5); hold on;
plot(t, w, 'b', 'LineWidth', 1.2); grid on; ylabel('Speed [rpm]');
legend('Reference', 'Measured', 'Location', 'northeast'); ylim([-1700 1700]);
nexttile; plot(t, e, 'r', 'LineWidth', 1); grid on; ylabel('Error [rpm]'); ylim([-200 200]);
nexttile; plot(t, u, 'Color', [0 0.5 0], 'LineWidth', 1.2); grid on;
ylabel('Duty [%]'); xlabel('Time [s]'); ylim([-105 105]);

% per-step metrics
prev = 0; n = numel(Ref_Levels);
M = zeros(n, 5);
for i = 1:n
    t0 = Ref_Time(i); R = Ref_Levels(i); st = R - prev;
    idx = t >= t0 + 1.2 & t < t0 + 2; seg = find(t >= t0 & t < t0 + 2);
    es = w(seg) - R;
    os = 0; if st ~= 0, os = max(0, max(sign(st)*es))/abs(st)*100; end
    k = find(abs(es) > max(0.05*abs(st), 15), 1, 'last');
    ts = 0; if ~isempty(k), ts = t(seg(k)) - t0; end
    M(i, :) = [R, mean(w(idx)) - R, std(w(idx)), os, ts];
    prev = R;
end
T = array2table(M, 'VariableNames', {'Ref_rpm', 'SSError_rpm', 'Noise_std_rpm', 'Overshoot_pct', 'Settling_s'});

artDir = fullfile(root, '02_SupportingArtifacts');
exportgraphics(fig, fullfile(artDir, 'M3_ClosedLoop.png'), 'Resolution', 150);

% markdown report
fid = fopen(fullfile(artDir, 'M3_ClosedLoopResults.md'), 'w');
fprintf(fid, '# DC Motor PI Speed Control - Hardware Results\n\n');
fprintf(fid, 'Arduino Uno, BTS7960 driver, Pololu 4841 (4.4:1, 12 V), encoder on D2/D3, Ts = %g ms.\n\n', Ts*1000);
fprintf(fid, '![Closed loop](M3_ClosedLoop.png)\n\n');
fprintf(fid, '## Controller\n\n| Item | Value |\n|---|---|\n');
fprintf(fid, '| Plant (identified) | K = %.2f rpm/%%, tau = %.1f ms |\n', Plant_K, Plant_Tau*1000);
fprintf(fid, '| PI gains | Kp = %.4f %%/rpm, Ki = %.3f %%/(rpm s) |\n', PI_Kp, PI_Ki);
fprintf(fid, '| Design | pole-zero cancellation, closed-loop tau = %.0f ms |\n', Spd_Tcl*1000);
fprintf(fid, '| Output limit | +/-100 %% duty, clamping anti-windup |\n');
fprintf(fid, '| Speed calibration | raw / %.4f (100 %% duty = 2200 rpm) |\n\n', Spd_CalDivisor);
fprintf(fid, '## Summary\n\n');
fprintf(fid, '- Max steady-state error: %.1f rpm\n', max(abs(M(:,2))));
fprintf(fid, '- Speed noise (std): %.1f-%.1f rpm\n', min(M(M(:,1)~=0,3)), max(M(:,3)));
fprintf(fid, '- Median overshoot: %.1f %%, median settling: %.2f s\n', median(M(:,4)), median(M(:,5)));
fprintf(fid, '- Duty range used: %.1f to %.1f %%\n', min(u), max(u));
fprintf(fid, '- Note: 0 -> -150 rpm step from standstill overshoots (static friction breakaway).\n\n');
fprintf(fid, '## Per-step results\n\n| Ref [rpm] | SS error [rpm] | Noise std [rpm] | Overshoot [%%] | Settling [s] |\n|---:|---:|---:|---:|---:|\n');
fprintf(fid, '| %.0f | %.1f | %.1f | %.1f | %.2f |\n', M.');
fclose(fid);
disp(T);
