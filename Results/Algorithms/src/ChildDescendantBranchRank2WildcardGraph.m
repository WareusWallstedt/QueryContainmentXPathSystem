format long
A = [
	0	1.850600	0.950300;
	1	3.748400	2.168800;
	2	80.937500	4.166100;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchRank2WildcardGraph.png');
