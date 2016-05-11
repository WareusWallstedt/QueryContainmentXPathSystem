format long
A = [
	0	1.790900	0.956200;
	1	3.835300	2.201500;
	2	80.598000	4.063700;
	3	1107.641000	6.620700;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchDepth2WildcardGraph.png');
