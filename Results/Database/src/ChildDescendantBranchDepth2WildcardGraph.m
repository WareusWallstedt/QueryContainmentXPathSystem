format long
A = [
	0	0.380000	9675.040000	9470.310000;
	1	0.390000	9514.320000	9547.950000;
	2	0.970000	9740.730000	9533.270000;
	3	1.190000	11775.650000	9521.440000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchDepth2WildcardGraph.png');
