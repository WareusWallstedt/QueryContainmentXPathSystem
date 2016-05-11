format long
A = [
	0	0.370000	9510.950000	9526.500000;
	1	0.450000	9576.230000	9581.740000;
	2	0.900000	9557.860000	9553.570000;
	3	1.330000	9748.410000	9535.830000;
	4	2.670000	9921.720000	10189.940000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchDepth2WildcardGraph.png');
