format long
A = [
	0	1.871300	1.128400;
	1	4.923000	2.203700;
	2	87.526600	4.297600;
	3	11690.931400	7.389600;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
set(gca,'xtick',0:3)
set(gca,'xlim',[0,3])
saveas(f, '../img/DescendantBranchDepth2Graph.png');
