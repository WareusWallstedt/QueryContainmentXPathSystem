format long
A = [
	0	0.360000	9618.970000	9982.270000;
	1	0.490000	10147.860000	10614.390000;
	2	14.650000	9901.390000	9572.770000;
	3	13.340000	10579.750000	9633.360000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchRank2Graph.png');
