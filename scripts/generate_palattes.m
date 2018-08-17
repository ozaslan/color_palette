maps = {'parula', 'jet', 'hsv', 'hot', 'cool','spring', ...
        'summer','autumn','winter','gray','bone','copper', ...
        'pink','lines','colorcube','prism','flag'};

for map = maps
    pname = map{1};
    cmap = colormap(pname)';
    fid = fopen(['../palettes/' pname '.palette'], 'w');
    fprintf(fid, '%.3f %.3f %.3f\n', cmap);
    fclose(fid);
end
