# Inventory Management System

This is a simple C-based Inventory Management System that helps manage product records efficiently.

## Features
- Add new products
- Display all products
- Search a product by ID
- Check low-stock products
- Update product details
- Delete products
- Calculate total inventory value
- Save and load product data from a file

## Technologies Used
- C Programming Language
- File Handling in C

## Project Files
- Product.c - Main source code
- Product.txt - File used to store product data

## Input Validation Included
This project includes validation for:
- Invalid menu choices
- Negative or zero product IDs
- Duplicate product IDs
- Empty product names
- Negative price values
- Negative quantity values
- Invalid numeric input

## How to Run
1. Open a C compiler such as GCC.
2. Compile the program:
   gcc Product.c -o Product
3. Run the program:
   ./Product

## Example Menu
1. Add Product
2. List of Product
3. Find the Product
4. Low Stock Product
5. Update Product
6. Delete Product
7. Total Inventory Value
8. Exit

## Project Description
This system stores product details such as:
- Product ID
- Product Name
- Product Price
- Product Quantity

The data is saved in Product.txt, so it remains available even after the program closes.

## Author
Snehal Kuber Chavan