format long
A = [
	0	1.876000	0.949900;
	1	4.373400	2.180000;
	2	63.116700	4.085600;
	3	6562.933200	6.965400;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchDepth2WildcardGraph.png');
