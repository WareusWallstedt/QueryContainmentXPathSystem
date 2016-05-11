format long
A = [
	0	1.915200	0.947500;
	1	4.899100	2.197400;
	2	87.192100	4.411600;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchRank2Graph.png');
