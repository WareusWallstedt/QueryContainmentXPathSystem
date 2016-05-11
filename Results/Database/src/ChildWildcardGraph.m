format long
A = [
	0	0.380000	9496.460000	9503.080000;
	1	86635.180000	98715.320000	98494.100000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildWildcardGraph.png');
