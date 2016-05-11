format long
A = [
	0	1.747800	1.056300;
	1	4.442900	2.277300;
	2	63.439900	4.135400;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchRank2WildcardGraph.png');
