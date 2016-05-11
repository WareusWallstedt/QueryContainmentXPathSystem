format long
A = [
	0	0.380000	9784.610000	9616.270000;
	1	0.470000	9536.780000	9742.280000;
	2	20.290000	9940.930000	9575.320000;
	3	24.250000	83980.350000	9925.270000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchRank2Graph.png');
