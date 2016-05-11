format long
A = [
	0	0.380000	9509.530000	9575.600000;
	1	637.730000	7865.500000	7870.070000;
	2	23412.220000	29221.210000	29114.060000;
	3	101685.230000	104455.670000	103842.290000;
	4	139018.750000	134725.390000	134841.610000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildGraph.png');
