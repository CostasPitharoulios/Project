# Polygonal Curves Clustering & LSH Hashing

Part 1:
Implementation of LSH (Locality-sensitive hashing) algorithm for the hashing of points and polygonal curves(sequences of points).

Part 2:
Clustering K-means/K-medoids for points and polygonal curves.
Employed various approaches:
Initialization:
- Random selection of K points/K curves
- K-means++
Assignment:
- Lloyd's assignment
- Assigment by Range search with LSH for points/curves (inverse assignment)
Update:
- Partitioning Aroung Medoids (PAM) a la Lloyds
- Mean Vector / DTW centroid curve

This project was developed in the context of the "Software Development for Hard Algorithmic Problems" course of the Departments of Infomatrics and Telecommunications of the University of Athems.
