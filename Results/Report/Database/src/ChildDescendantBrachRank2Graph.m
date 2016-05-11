format long
A = [
	0	0.370000	9398.860000	9367.490000;
	1	0.470000	9359.040000	9348.940000;
	2	14.600000	9428.720000	9424.060000;
	3	13.310000	10246.440000	9402.090000;
	4	14.280000	435718.630000	9416.910000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBrachRank2Graph.png');
