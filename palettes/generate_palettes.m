close all;
clear all;
clc;

names = cell(0);
names{end + 1} = 'parula';
names{end + 1} = 'jet';
names{end + 1} = 'hsv';
names{end + 1} = 'hot';
names{end + 1} = 'cool';
names{end + 1} = 'spring';
names{end + 1} = 'summer';
names{end + 1} = 'autumn';
names{end + 1} = 'winter';
names{end + 1} = 'gray';
names{end + 1} = 'bone';
names{end + 1} = 'copper';
names{end + 1} = 'pink';
names{end + 1} = 'lines';
names{end + 1} = 'colorcube';
names{end + 1} = 'prism';
names{end + 1} = 'flag';

for i = 1 : numel(names)
    cmap = colormap(names{i});
    fid = fopen([names{i} '.palette'], 'w');
    fprintf(fid, '%.3f %.3f %.3f\n', cmap');
    fclose(fid);
end
close all;