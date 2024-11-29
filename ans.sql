1a) select s.sale_id, s.total_price from sales s where s.sale_date='2024-01-03' and s.total_price >500;
1b) select p.product_id , product_name from products p where p.unit_price>100;
+------------+--------------+
| product_id | product_name |
+------------+--------------+
|        101 | Laptop       |
|        102 | Mobile       |
+------------+--------------+

2)select sum(s.total_price) from sales s join products p on s.product_id=p.product_id where p.category='Electronics
';
+--------------------+
| sum(s.total_price) |
+--------------------+
|               3630 |
+--------------------+

3)  select category, avg(unit_price) as avg_price
    -> from products
    -> group by category
    -> ;
+-------------+----------------+
| category    | avg_price |
+-------------+----------------+
| Electronics |       173.0000 |
+-------------+----------------+

4) SELECT p.product_id, p.product_name, SUM(s.quantity_sold) as total from sales s join products p on s.product_id=p.product_id group by p.product_id having total>30;

5) select avg(s.quantity_sold) as total from sales s join products p on s.product_id=p.product_id where p.unit_price
>100;
+--------+
| total  |
+--------+
| 4.0000 |
+--------+

6) SELECT s.sale_id, s.product_id, s.quantity_sold, s.sale_date, s.total_price
FROM sales s
WHERE s.quantity_sold > (
    SELECT AVG(quantity_sold)
    FROM sales
);
+---------+------------+---------------+------------+-------------+
| sale_id | product_id | quantity_sold | sale_date  | total_price |
+---------+------------+---------------+------------+-------------+
|       1 |        101 |             5 | 2024-01-01 |        2500 |
|       5 |        105 |             6 | 2024-01-03 |          90 |
+---------+------------+---------------+------------+-------------+

7) SELECT p.product_name, p.category, p.unit_price
FROM products p
JOIN sales s ON p.product_id = s.product_id
WHERE s.quantity_sold > (
    SELECT AVG(quantity_sold)
    FROM sales
);
+--------------+-------------+------------+
| product_name | category    | unit_price |
+--------------+-------------+------------+
| Laptop       | Electronics |        500 |
| Mouse        | Electronics |         15 |
+--------------+-------------+------------+