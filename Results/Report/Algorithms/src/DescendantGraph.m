format long
A = [
	0	1.882700	0.937700;
	1	2.744700	1.820100;
	2	4.412700	1.622100;
	3	8.361300	1.932100;
	4	15.423600	2.295000;
	5	30.916500	2.827800;
	6	65.716100	3.006700;
	7	143.456200	3.281600;
	8	313.690300	3.626600;
	9	696.820400	3.914000;
	10	1528.439500	4.349600;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantGraph.png');
