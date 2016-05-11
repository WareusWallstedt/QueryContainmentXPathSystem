format long
A = [
	0	1.800400	0.939000;
	1	2.078900	1.840700;
	2	2.891400	1.598500;
	3	3.168800	1.915100;
	4	3.875400	2.303300;
	5	4.228300	2.609600;
	6	4.881200	2.939300;
	7	5.320700	3.224100;
	8	5.997400	3.506200;
	9	6.462900	3.853800;
	10	6.830800	4.284500;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildGraph.png');
