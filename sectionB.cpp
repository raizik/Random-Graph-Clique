#include <iostream>
#include <math.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#define N 1000
#define EXPERIMENTS 10000

int main() {

    int* verticesList = new int[N];
    int* nextVertexCandidates = new int[N];
    int** adjecencyMatrix = new int*[N];
    for (int i = 0; i < N; ++i)
        adjecencyMatrix[i] = new int[N];
    int* clique = new int[N];
    int* resultsVector = new int[EXPERIMENTS];
    for (int j=0; j<N; j++){
        clique[j] = 0;
        verticesList[j] = 0;
        nextVertexCandidates[j] = 0;
    }
    for (int j=0; j<EXPERIMENTS; j++){
        resultsVector[j] = 0;
    }
    //init to zeros
    //initMatrix(adjecencyMatrix);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            adjecencyMatrix[i][j] = 0;
        }
    }



    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    srand ( std::time(&now) );

    for (int i_exp=0; i_exp<EXPERIMENTS; i_exp++){
        //now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        //srand ( std::time(&now) );
        for (int j=0; j<N; j++){
            clique[j] = 0;
            verticesList[j] = 0;
            nextVertexCandidates[j] = 0;
        }
        //init to zeros
        //initMatrix(adjecencyMatrix);
        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                adjecencyMatrix[i][j] = 0;
            }
        }
        //G(n,1/2) graph creation
        int graph_size = 0;
        for (int i_vertex1=0; i_vertex1<N; i_vertex1++){
            for (int i_vertex2=0; i_vertex2<N && i_vertex2 < i_vertex1; i_vertex2++){
                //todo: fix
                //std::srand( std::time(0) );
                /* std::default_random_engine generator;
                 generator.seed(std::rand());
                 //printf("std::rand() = %d", std::rand() % N);
                 std::uniform_real_distribution<double> distribution(0.0,1.0);
                 double rand_prob = distribution(generator);*/
                //bernouli

                std::default_random_engine generator_b( std::random_device{}() );
                generator_b.seed(rand());

                std::bernoulli_distribution dist_b(0.5);
                //generator.seed(std::rand());
                //double rand_prob = ((double)rand() / (RAND_MAX));
                //printf("rand_prob = %f \n", rand_prob);
                //printf("dist_b(gen_b) = %d\n", dist_b(generator_b));
                if (/*rand_prob <=0.5 && rand_prob >= 0.49*/dist_b(generator_b)) {
                    //printf("bernoulli 1 \n ");
                    adjecencyMatrix[i_vertex1][i_vertex2] = 1;
                    //assuming G(n, 1/2) is undirected
                    adjecencyMatrix[i_vertex2][i_vertex1] = 1;
                    graph_size++;
                    //printf("(v1: %d, v2: %d), \n", i_vertex1, i_vertex2);
                }
            }
        }
        printf("graph size = %d\n", graph_size);
        //clique creation
        //create clique candidates list
        /*
         * init: choose a random first_vertex to the clique
         *       lastInsertedVertex <- first_vertex
         * loop: construct the nextVertexCandidates list for lastInsertedVertex
         *       (if nextVertexCandidates list is empty -- exit loop)
         *       Choose arbitrary vertex out of the nextVertexCandidates list V
         *       set lastInsertedVertex <- V
         */
        /*  std::random_device rd_one;  //Will be used to obtain a seed for the random number engine
          std::mt19937 gen_one(rd_one()); //Standard mersenne_twister_engine seeded with rd()
          std::uniform_int_distribution<> dis_one(0, N-1);
          int firstVertex = dis_one(gen_one);*/
        //time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        //std::default_random_engine generator_one;
        //generator_one.seed(std::rand());
        /*std::default_random_engine generator_one( std::random_device{}() );
        generator_one.seed(std::rand());
        std::uniform_int_distribution<int> distribution_one(0,N-1);
        int firstVertex = distribution_one(generator_one);*/
        //now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        //srand ( std::time(&now) );
        //srand(rand());
        //section B
        int max_deg = 0;
        int deg_count = 0;
        int vertex_max_deg = 0;
        for (int i=0; i<N; i++){
            deg_count = 0;
            //int vertex_deg = verticesList[i];
            for (int v_n=0; v_n < N; v_n++){
                if (adjecencyMatrix[i][v_n] == 1)
                    deg_count++;
                if (deg_count >= max_deg){
                    max_deg = deg_count;
                    vertex_max_deg = i;
                }

            }
        }
        int firstVertex = vertex_max_deg;
        //todo: section A
        //int firstVertex = rand() % N;
        //srand (time(NULL));
        //int firstVertex = rand() % (N-1);
        printf("first vertex = %d\n", firstVertex);
        clique[firstVertex] = 1;
        int lastInsertedVertex = firstVertex;
        bool finished = false;
        //int nextVertexCandidates[N] = {0};
        bool candidatesListEmpty = true;
        //int verticesList[N] = {0};
        int vIndex = 0;
        bool vertexConnectedCurrClique = true;
        while (!finished){
            //srand ( std::time(&now) );
            candidatesListEmpty = true;
            vIndex = 0;
            vertexConnectedCurrClique = true;
            //construct nextVertexCandidates for lastInsertedVertex
            for (int vertex = 0; vertex < N; vertex++){
                //check connectivity to all vertices in the current clique
                for (int clique_v = 0; clique_v < N && vertexConnectedCurrClique; clique_v++){
                    if (adjecencyMatrix[vertex][clique_v] == 0 && clique[clique_v] == 1)
                        vertexConnectedCurrClique = false;
                }
                //chosen vertex is connected to all current clique vertices -- add it to candidates list
                if (vertexConnectedCurrClique){
                    nextVertexCandidates[vertex] = 1;
                    verticesList[vIndex] = vertex;
                    vIndex++;
                    candidatesListEmpty = false;
                }
                vertexConnectedCurrClique = true;
            }
            //if empty -- set finished to true and exit loop
            if (candidatesListEmpty){
                //printf("here candidatesListEmpty is true\n");
                finished = true;
                continue;
            }
            //choose a random vertex out of nextVertexCandidates list and set lastInsertedVertex to it
            //printf("CandidatesListEmpty is false \n");

            /*std::default_random_engine generator_two( std::random_device{}() );
             generator_two.seed(std::rand());
             std::uniform_int_distribution<int> distribution_two(0,vIndex-1);
             lastInsertedVertex = verticesList[distribution_two(generator_two)];*/
            //now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            //srand ( std::time(&now) );
            //srand(rand());
            //section B

            max_deg = 0;
            vertex_max_deg = 0;
            for (int i=0; i<vIndex; i++){
                deg_count = 0;
                int vertex_deg = verticesList[i];
                for (int v_n=0; v_n < N; v_n++){
                    if (adjecencyMatrix[vertex_deg][v_n] == 1)
                        deg_count++;
                    if (deg_count >= max_deg){
                        max_deg = deg_count;
                        vertex_max_deg = vertex_deg;
                    }

                }
            }
            lastInsertedVertex = vertex_max_deg;
            //todo: section A
            //lastInsertedVertex = verticesList[rand() % vIndex];
            //rintf("lastinsertedvertex = %d\n", lastInsertedVertex);
/*
            std::random_device rd_two;  //Will be used to obtain a seed for the random number engine
            std::mt19937 gen_two(rd_two()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_int_distribution<> dis_two(0, N-1);
            lastInsertedVertex = verticesList[dis_two(gen_two)];
            printf("lastinsertedvertex = %d\n", lastInsertedVertex);*/
            /*
            std::default_random_engine generator_two;
            generator_two.seed(std::rand());
            std::uniform_int_distribution<int> distribution_two(0,N-1);
            lastInsertedVertex = verticesList[distribution_two(generator_two)];*/
            //srand (time(NULL));
            //lastInsertedVertex = verticesList[rand() % (vIndex - 1)];
            //printf("last inserted vertex = %d \n", lastInsertedVertex);
            //turn on its flag in clique array
            clique[lastInsertedVertex] = 1;
            for (int j=0; j<N; j++){
                verticesList[j] = 0;
                nextVertexCandidates[j] = 0;
            }
            vIndex = 0;
            // printf("end of finished loop \n");
            //now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            //srand ( std::time(&now) );
        }
        //printf("post finished loop \n");
        //bool connectedToAllCliqueVertices = true;
        int cliqueSize = 0;
        for (int i=0; i<N; i++){
            if (clique[i])
                cliqueSize ++;
        }
        //if (i_exp == 0 || (i_exp > 0 && resultsVector[i_exp - 1] != cliqueSize))
        resultsVector[i_exp] = cliqueSize;
        //initMatrix(adjecencyMatrix);
        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                adjecencyMatrix[i][j] = 0;
            }
        }
        printf("i_exp=%d \n", i_exp);
    }
    int maxClique = 0;
    double avgClique = 0;
    int minClique = N;
    int resVectorSize = 0;
    for (int s = 0; s<EXPERIMENTS; s++){
        if (resultsVector[s] >= maxClique)
            maxClique = resultsVector[s];
        avgClique += (double)resultsVector[s];
        if (resultsVector[s] <= minClique)
            minClique = resultsVector[s];
    }

    delete[]  verticesList;
    delete[] nextVertexCandidates;
    delete[] clique;
    delete[] resultsVector;
    for (int i = 0; i < N; ++i)
        delete [] adjecencyMatrix[i];
    delete [] adjecencyMatrix;
    printf("maxClique = %d \n", maxClique);
    printf("minClique = %d \n", minClique);
    printf("avgClique = %.2f\n", avgClique / EXPERIMENTS);
    return maxClique;
}//
// Created by ledra on 2/3/2020.
//

