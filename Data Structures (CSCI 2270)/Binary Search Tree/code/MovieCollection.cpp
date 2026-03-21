#include "MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

static void destroyTreeHelper(Movie* node);
static void insertHelper(Movie*& current, Movie* newMovie);
static void inOrderPrint(Movie* node);
static Movie* searchMovieHelper(Movie* node, const string& movieName);
static void reverseOrderByDirector(Movie* node, const string& director);
static void printLeavesHelper(Movie* node);
static int heightEdgesHelper(Movie* node);
static int countGenreHelper(Movie* node, const string& genre);



MovieCollection::MovieCollection() {
    root = nullptr;
}


MovieCollection::~MovieCollection() {
    destroyTreeHelper(root);
    root = nullptr;
}


void MovieCollection::addMovie(string movieName, string director, string genre) {
   Movie* newMovie = new Movie(movieName, director, genre);
   newMovie->left = nullptr;
   newMovie->right = nullptr;

   if(root == nullptr){
    root = newMovie;
    return;
   }
   insertHelper(root, newMovie);
}


void MovieCollection::showMovieCollection() {
    if(root == nullptr){
        cout << "Collection is empty." << endl;
        return;
    }
    inOrderPrint(root);
}


void MovieCollection::showMovie(string movieName) {
    Movie* found = searchMovieHelper(root, movieName);
    if (found != nullptr) {
        cout << "Movie:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << found->movieName << endl;
        cout << "Director :" << found->director << endl;
        cout << "Genre :" << found->genre << endl;       
    } else {
        cout << "Movie not found." << endl;
    }
}


void MovieCollection::showMoviesByDirector(string director) {
    cout << "Movies Directed By: " << director << endl;
    reverseOrderByDirector(root, director);
}


void MovieCollection::printLeaves()
{
   printLeavesHelper(root);
}

int MovieCollection::getHeightOfMovieCollection() {
    if(root == nullptr){
        return EMPTY_TREE_ERROR;
    }
    return heightEdgesHelper(root);

    return 0;
}

static void destroyTreeHelper(Movie* node) {
    if (node == nullptr) return;
    destroyTreeHelper(node->left);
    destroyTreeHelper(node->right);
    delete node;
}

static void insertHelper(Movie*& current, Movie* newMovie) {
    if (current == nullptr) {
        current = newMovie;
        return;
    }
    if (newMovie->movieName < current->movieName) {
        insertHelper(current->left, newMovie);
    } else {
        insertHelper(current->right, newMovie);
    }
}

static void inOrderPrint(Movie* node) {
   if (node == nullptr) return;
    inOrderPrint(node->left);
    cout << "MOVIE: " << node->movieName
         << " DIRECTOR: " << node->director
         << " GENRE: " << node->genre << endl;

    inOrderPrint(node->right);
}

static Movie* searchMovieHelper(Movie* node, const string& movieName) {
    if (node == nullptr) return nullptr;
    if (movieName == node->movieName) return node;
    if (movieName < node->movieName) return searchMovieHelper(node->left, movieName);
    return searchMovieHelper(node->right, movieName);
}

static void reverseOrderByDirector(Movie* node, const string& director) {
    if (node == nullptr) return;
    reverseOrderByDirector(node->right, director);
    if (node->director == director) {
        cout << node->movieName << " GENRE: " << node->genre << endl;
    }
    reverseOrderByDirector(node->left, director);
}

static void printLeavesHelper(Movie* node) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        cout << "MOVIE: " << node->movieName
             << " DIRECTOR: " << node->director
             << " GENRE: " << node->genre << endl;
        return;
    }
    printLeavesHelper(node->left);
    printLeavesHelper(node->right);
}

static int heightEdgesHelper(Movie* node) {
    if (node == nullptr) return -1;
    int lh = heightEdgesHelper(node->left);
    int rh = heightEdgesHelper(node->right);
    return (lh > rh ? lh : rh) + 1;
}

static int countGenreHelper(Movie* node, const string& genre) {
    if (node == nullptr) {
        return 0;
    }

    int count = 0;

    if (node->genre == genre) {
        count = count + 1;
    }

    int leftCount = countGenreHelper(node->left, genre);
    int rightCount = countGenreHelper(node->right, genre);

    count = count + leftCount;
    count = count + rightCount;

    return count;
}