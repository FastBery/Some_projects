// // #pragma once
// #include <vector>
// #include <cstdlib>
// #include <algorithm>
// #include <variant>
// #include "vec3.h"
// #include "ray.h"
// #include "functions.h"
// //#include "maybe_two_intersections.h"
// /*
// Tree cons(Tree left, b_b value, Tree right){
//     Tree a = static_cast<Tree>(std::malloc(sizeof(boxnode)));
//     a->box = value;
//     a->next = boxnode::branches({left, right});
//     return a;
// };*/
// /*
// Tree createTree(TriangleRange range){
//     triangle *mid = range.begin + (range.end - range.begin) / 2;
//     if (mid == range.begin){
//         Tree node;
//         *node = {triangle_to_b_b(*mid), *mid};
//         return node;
//     }
//     Tree right = createTree({range.begin, mid});
//     Tree left = createTree({mid + 1, range.end});
//     return cons(left, array_to_one(range), right);
// }*/
// //выбери какую из createTree оставлять

// TriangleRange range_of_triangles;
// int i = find_max_side(array_to_one(range_of_triangles));

