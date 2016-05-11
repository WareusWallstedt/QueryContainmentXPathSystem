format long
A = [
	0	0.370000	9661.660000	9504.370000;
	1	5.540000	9555.740000	9540.150000;
	2	20.250000	9748.080000	9575.680000;
	3	36.510000	25873.430000	9662.430000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchDepth2Graph.png');
