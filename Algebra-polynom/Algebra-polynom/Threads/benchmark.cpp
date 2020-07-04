#include "Polynom/Polynom.h"
#include <chrono>
#include <iostream>
#include <vector>

int main() {
    /*std::vector<std::vector<long long>> polyVector = { {0,2}, {1,3}, {2,1}, {3,3}, {4,2}, {5,3}, {6,2}, {7,3}, {8,2}, {9,3},
        {10,2}, {11,3}, {12,2}, {13,3}, {14,2}, {15,3}, {16,2}, {17,3}, {18,2}, {19,3}, {22,1} };
    Polynom polynom(5, polyVector);*/

    /*auto polynom = Polynom::generateRandomPoly(2, 433, true);
    std::cout << polynom.show() << std::endl << std::endl;*/

    Polynom polynom(2, "1 + 1*x + 1*x^2 + 1*x^3 + 1*x^4 + 1*x^5 + 1*x^6 + 1*x^8 + 1*x^10 + 1*x^17 + 1*x^18 + 1*x^19 + 1*x^21 + 1*x^22 + 1*x^24 + 1*x^25 + 1*x^26 + 1*x^28 + 1*x^32 + 1*x^36 + 1*x^37 + 1*x^40 + 1*x^46 + 1*x^47 + 1*x^48 + 1*x^50 + 1*x^53 + 1*x^54 + 1*x^55 + 1*x^57 + 1*x^59 + 1*x^61 + 1*x^62 + 1*x^63 + 1*x^64 + 1*x^65 + 1*x^66 + 1*x^68 + 1*x^70 + 1*x^72 + 1*x^73 + 1*x^75 + 1*x^76 + 1*x^78 + 1*x^79 + 1*x^80 + 1*x^87 + 1*x^88 + 1*x^89 + 1*x^90 + 1*x^94 + 1*x^96 + 1*x^97 + 1*x^98 + 1*x^99 + 1*x^100 + 1*x^103 + 1*x^104 + 1*x^106 + 1*x^107 + 1*x^109 + 1*x^111 + 1*x^114 + 1*x^119 + 1*x^120 + 1*x^122 + 1*x^125 + 1*x^126 + 1*x^130 + 1*x^131 + 1*x^133 + 1*x^134 + 1*x^135 + 1*x^138 + 1*x^140 + 1*x^143 + 1*x^145 + 1*x^146 + 1*x^147 + 1*x^150 + 1*x^151 + 1*x^152 + 1*x^153 + 1*x^155 + 1*x^159 + 1*x^160 + 1*x^161 + 1*x^163 + 1*x^166 + 1*x^167 + 1*x^169 + 1*x^171 + 1*x^172 + 1*x^175 + 1*x^176 + 1*x^180 + 1*x^182 + 1*x^183 + 1*x^186 + 1*x^188 + 1*x^189 + 1*x^190 + 1*x^191 + 1*x^193 + 1*x^197 + 1*x^199 + 1*x^201 + 1*x^202 + 1*x^203 + 1*x^205 + 1*x^206 + 1*x^210 + 1*x^213 + 1*x^214 + 1*x^215 + 1*x^216 + 1*x^217 + 1*x^219 + 1*x^220 + 1*x^221 + 1*x^224 + 1*x^225 + 1*x^228 + 1*x^229 + 1*x^231 + 1*x^232 + 1*x^233 + 1*x^235 + 1*x^236 + 1*x^238 + 1*x^239 + 1*x^240 + 1*x^242 + 1*x^245 + 1*x^246 + 1*x^247 + 1*x^248 + 1*x^252 + 1*x^253 + 1*x^255 + 1*x^256 + 1*x^259 + 1*x^260 + 1*x^261 + 1*x^263 + 1*x^264 + 1*x^266 + 1*x^269 + 1*x^272 + 1*x^274 + 1*x^275 + 1*x^279 + 1*x^286 + 1*x^288 + 1*x^289 + 1*x^292 + 1*x^293 + 1*x^294 + 1*x^296 + 1*x^300 + 1*x^302 + 1*x^303 + 1*x^305 + 1*x^307 + 1*x^308 + 1*x^310 + 1*x^311 + 1*x^312 + 1*x^314 + 1*x^317 + 1*x^318 + 1*x^320 + 1*x^321 + 1*x^323 + 1*x^324 + 1*x^331 + 1*x^336 + 1*x^339 + 1*x^340 + 1*x^344 + 1*x^350 + 1*x^351 + 1*x^353 + 1*x^355 + 1*x^358 + 1*x^360 + 1*x^362 + 1*x^363 + 1*x^365 + 1*x^366 + 1*x^368 + 1*x^369 + 1*x^370 + 1*x^371 + 1*x^375 + 1*x^377 + 1*x^380 + 1*x^381 + 1*x^386 + 1*x^389 + 1*x^391 + 1*x^394 + 1*x^396 + 1*x^399 + 1*x^401 + 1*x^402 + 1*x^403 + 1*x^405 + 1*x^407 + 1*x^411 + 1*x^412 + 1*x^414 + 1*x^416 + 1*x^421 + 1*x^423 + 1*x^430 + 1*x^431", 'x');
    std::cout << polynom.show() << std::endl << std::endl;

    auto start = std::chrono::system_clock::now();
    std::cout << polynom.berlekampAlgorithm() << std::endl;
    auto stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken by simple function: " << duration.count() << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    std::cout << polynom.berlekampAlgorithmMultithreaded() << std::endl;
    stop = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken by parallel function: " << duration.count() << " ms" << std::endl;
}