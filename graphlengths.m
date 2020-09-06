MIN = 0;
MAX = 2000000000000;
DX = 1000000000;
rawx = MIN:DX:MAX;
rawx = rawx';

sqrtx = sqrt(rawx);
cbrtx = rawx.^(1/3);
logx = log(rawx);

% graphLength(1);
% graphLengthCustom(1,sqrtx,'sqrt');
% graphLengthCustom(1,cbrtx,'cbrt');
% graphLengthCustom(1,logx,'log');

% graphLength(16);
% graphLengthCustom(16,sqrtx,'sqrt');
% graphLengthCustom(16,cbrtx,'cbrt');
% graphLengthCustom(16,logx,'log');

% graphLength(19);
% graphLengthCustom(19,sqrtx,'sqrt');
% graphLengthCustom(19,cbrtx,'cbrt');
% graphLengthCustom(19,logx,'log');
% looks like 16 stretched horizontally?
data = readLenFile(19);
%rawx = MIN:(DX/2):(MAX/2);
%rawx = rawx';
%scatter(rawx, data(:,2), 10);
scatter(data(:,1), data(:,2), 10);
ylim([0 2500000]);
saveas(gcf, '19/compressed.png');

% graphLength(20);
% graphLengthCustom(20,sqrtx,'sqrt'); %%this for sure
% graphLengthCustom(20,cbrtx,'cbrt');
% graphLengthCustom(20,logx,'log');

function lendata = readLenFile(num)
    filename = sprintf('%d/lengths.txt', num);
    fileID = fopen(filename, 'r');
    formatSpec = '%lu %f';
    sizeA = [2 Inf];
    A = fscanf(fileID, formatSpec, sizeA);
    lendata = A';
end

function graphLength(num)
    data = readLenFile(num);
    filename = sprintf('%d/tapelength.png', num);
    scatter(data(:,1), data(:,2), 10);
    saveas(gcf, filename);
end

function graphLengthCustom(num,X,fname)
    data = readLenFile(num);
    filename = sprintf('%d/%s.png', num, fname);
    y = data(:,2);
    
    %linear regression
    regressX = [ones(length(X),1) X];
    reg = regressX\y;
    regressY = regressX*reg;
    
    scatter(X, y, 10);
    hold on;
    pr = plot(X,regressY,'--');
    hold off;
    
    label = sprintf('%.2f + %.2f x',reg(1),reg(2));
    legend([pr],{label},'Location','southeast');
    saveas(gcf, filename);
end