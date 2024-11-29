create table sales(
    sale_id int PRIMARY KEY,
    product_id int,
    quantity_sold int,
    sale_date DATE,
    total_price int,

    FOREIGN KEY (product_id) REFERENCES products(product_id)
);

insert into sales values
(1, 101, 5, '2024-01-01', 2500),
(2, 102, 3, '2024-01-02', 900),
(3, 103, 2, '2024-01-02', 60),
(4, 104, 4, '2024-01-03', 80),
(5, 105, 6, '2024-01-03', 90);


create table products(
    product_id int PRIMARY KEY,
    product_name varchar(50),
    category varchar(50),
    unit_price int
);

insert into products VALUES
(101,'Laptop','Electronics',500),
(102,'Mobile','Electronics',300),
(103,'Headphone','Electronics',30),
(104,'Keyboard','Electronics',20),
(105,'Mouse','Electronics',15);


-- Ques 1: a) Retrieve the sales id and total price from the sales table for sales made on 2024-01-03 and total price >500.
--         b) Retrieve the product id and product name from the products table for products with a unit price >100

-- Ques 2: Calculate the total revenue generated from sales of products in electronics category.
-- Ques 3: Find the product category with highest av unit price
-- Ques 4: Identify products with total sales excedding 30
-- Ques 5: Determine the avg quantity sold for products with unit price>100
-- Ques 6: Identify sales where the quantity sold is greater than avg quantity sold
-- Ques 7: Retrieve the product details , name, category, unit price for products that have quantity sold> than avg quantity sold across all products



SELECT sale_id, total_price 
FROM sales
WHERE sale_date = '2024-01-03' AND total_price > 500;

SELECT SUM(s.total_price) AS total_revenue
FROM sales s
JOIN products p ON s.product_id = p.product_id
WHERE p.category = 'Electronics';

SELECT category, AVG(unit_price) AS avg_unit_price
FROM products
GROUP BY category
ORDER BY avg_unit_price DESC
LIMIT 1;

SELECT p.product_id, p.product_name, SUM(s.quantity_sold) AS total_quantity_sold
FROM sales s
JOIN products p ON s.product_id = p.product_id
GROUP BY p.product_id, p.product_name
HAVING total_quantity_sold > 30;


SELECT AVG(s.quantity_sold) AS avg_quantity_sold
FROM sales s
JOIN products p ON s.product_id = p.product_id
WHERE p.unit_price > 100;
SELECT sale_id, product_id, quantity_sold, sale_date, total_price
FROM sales
WHERE quantity_sold > (SELECT AVG(quantity_sold) FROM sales);
SELECT p.product_name, p.category, p.unit_price
FROM products p
JOIN (
    SELECT product_id, SUM(quantity_sold) AS total_quantity_sold
    FROM sales
    GROUP BY product_id
) s ON p.product_id = s.product_id
WHERE s.total_quantity_sold > (
    SELECT AVG(quantity_sold)
    FROM sales
);


