format long
A = [
	0	1.810800	1.190400;
	1	4.946000	2.224200;
	2	87.498700	4.377000;
	3	49508.931800	8.496900;
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
saveas(f, '../img/DescendantBranchRank2Graph.png');
