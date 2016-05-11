format long
A = [
	0	0.320000	9523.700000	9506.770000;
	1	0.440000	9523.500000	9546.560000;
	2	0.900000	9663.420000	9624.420000;
	3	2.060000	72537.250000	9541.040000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchRank2WildcardGraph.png');
