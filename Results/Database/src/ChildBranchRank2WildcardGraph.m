format long
A = [
	0	0.340000	9580.690000	9552.990000;
	1	0.510000	9534.480000	9577.510000;
	2	0.920000	9628.310000	9851.460000;
	3	1.400000	9511.270000	9512.320000;
	4	1.440000	9588.420000	9558.470000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchRank2WildcardGraph.png');
