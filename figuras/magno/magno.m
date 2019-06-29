Base = load('erro.txt');
j = 1;
for i = 1 : 4
    figure((j+1)/2);
    plot(Base(:,9),Base(:,j),'b','LineWidth',2.5);
    set(gca,'FontSize',14)
    grid on
    hold on
    plot(Base(:,9),Base(:,j+1),'r','LineWidth',2.5);
    set(gca,'FontSize',14)
    grid on
    j = j + 2;
   % if i == 1
   %         legend('Medições do protótipo [A]','Medições do alicate [A]')
   % elseif i == 2
   %         legend('Medições do protótipo [V]','Medições do alicate [V]')
   % elseif i == 3
   %         legend('Medições do protótipo [Hz]','Medições do alicate [Hz]')
   % elseif i == 4
   %         legend('Medições do protótipo [W]','Medições do alicate [W]')
   % end
   if i == 1
           legend('Erro relativo [%]','Erro absoluto [A]') 
   elseif i == 2
           legend('Erro relativo [%]','Erro absoluto [V]')
   elseif i == 3
           legend('Erro relativo [%]','Erro absoluto [Hz]')
   elseif i == 4
           legend('Erro relativo [%]','Erro absoluto [W]')
   end
   
    alldatacursors = findall(gcf,'type','hggroup')
    set(alldatacursors,'FontSize',16)
    set(alldatacursors,'FontName','Times')
    set(alldatacursors, 'FontWeight', 'bold')
   
end