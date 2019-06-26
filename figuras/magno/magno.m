Base = load('magno.txt');
j = 1;
for i = 1 : 4
    figure((j+1)/2);
    plot(Base(:,9),Base(:,j),'b','LineWidth',2.5);
    hold on
    plot(Base(:,9),Base(:,j+1),'r','LineWidth',2.5);
    j = j + 2;
    legend('Medição da placa','Medição do alicate')
end