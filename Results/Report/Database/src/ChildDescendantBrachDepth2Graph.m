format long
A = [
	0	0.370000	9370.660000	9410.190000;
	1	1.750000	9388.610000	9389.080000;
	2	14.730000	9438.730000	9393.560000;
	3	18.940000	9626.380000	9388.480000;
	4	55.060000	13833.460000	9456.940000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBrachDepth2Graph.png');
