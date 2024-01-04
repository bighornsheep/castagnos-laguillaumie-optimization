/**
 * @file closest_23.h
 * Computes 2,3 representations using a greedy k-nearest approximation.
 */

#pragma once
#ifndef CLOSEST_23__INCLUDED
#define CLOSEST_23__INCLUDED

#include <gmp.h>
#include <stdint.h>

#include "liboptarith/group.h"

/**
 * Representations are the sum of all terms where each term is sign * 2^a * 3^b
 */
typedef struct {
  int sign;
  int a;
  int b;
} two_three_term_t;

void print_two_three_terms(const two_three_term_t* terms, const int term_count);

/**
 * Representation is given as an array 'A' such that
 * N = ((((A[0].b*A[0].a) \pm A[1].b)*A[1].a) \pm A[2].b)*A[2].a ....
 *
 * where A[i].b is added if the high bit of 'b' is clear,
 * and subtracted if the high bit of 'b' is set.
 *
 * We use the high bit so that if 'b' is 0, we can still distinguish between
 * a 'b' that should be added and a 'b' that should be subtracted.
 */
typedef struct {
  uint16_t a;
  uint16_t b;
} factored_two_three_term16_t;

void print_factored_two_three_term16(
    const factored_two_three_term16_t* terms,
    const int term_count);

/**
 * Returns an array of two_three_term_t and the term_count.
 * Caller must 'free()' the returned array.
 *
 * The representation is generated by repeatedly finding the k closest 2^a*3^b
 * when we have k reps for x, we return the least costly.
 */
two_three_term_t* rep_prune_closest(
    int* term_count,
    const mpz_t x,
    const group_cost_t* costs,
    const int keep_count);

/**
 * Computes the factored representation of a 2,3 number.
 * Caller is responsible for the lifetime of the returned object.
 * The two-three representation passed in is also sorted by the 'a' component.
 */
factored_two_three_term16_t* factored_rep(
    int* term_count,
    two_three_term_t* rep,
    int rep_count);

/**
 * Returns a 2,3 16 bit factored representation of the number x
 * using a gready k-closest algorithm.
 * 
 * The caller is responsible for the lifetime of the returned object.
 * 
 * This function essentially calls rep_prune_closest()
 * and then factored_rep().
 */
factored_two_three_term16_t* factored_rep_prune_closest(
    int* term_count,
    const mpz_t x,
    const group_cost_t* costs,
    const int keep_count);

#endif

