format long
A = [
	0	0.370000	9478.500000	9746.470000;
	1	0.430000	9580.750000	9811.110000;
	2	0.780000	10846.810000	10366.090000;
	3	1.440000	459444.560000	9517.320000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchRank2WildcardGraph.png');
