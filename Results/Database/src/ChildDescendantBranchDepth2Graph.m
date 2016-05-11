format long
A = [
	0	0.370000	9564.900000	9637.630000;
	1	1.790000	9797.820000	9649.420000;
	2	14.440000	9575.610000	9521.050000;
	3	19.130000	9945.300000	9628.030000;
	4	55.120000	13840.850000	9549.060000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchDepth2Graph.png');
