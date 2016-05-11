format long
A = [
	0	1.930400	0.947300;
	1	3.040800	1.855000;
	2	3.116100	1.609000;
	3	5.015400	1.940000;
	4	5.653700	2.317300;
	5	9.074600	2.626200;
	6	10.358900	3.147900;
	7	17.811400	3.283100;
	8	18.204600	3.744800;
	9	36.650500	3.925800;
	10	38.334200	4.487100;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantGraph.png');
