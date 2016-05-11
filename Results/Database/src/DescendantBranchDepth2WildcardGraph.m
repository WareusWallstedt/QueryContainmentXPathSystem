format long
A = [
	0	0.420000	10363.110000	10045.320000;
	1	0.450000	9631.550000	9587.430000;
	2	0.840000	9699.100000	10264.190000;
	3	1.040000	23453.460000	9538.840000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchDepth2WildcardGraph.png');
