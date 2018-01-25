/**
  Compatibility shims, allowing caml_z.c to call BSDNT as if it were GMP.

  This file is part of the Zarith library
  http://forge.ocamlcore.org/projects/zarith .
  It is distributed under LGPL 2 licensing, with static linking exception.
  See the LICENSE file included in the distribution.

*/

#define mp_limb_t word_t
#define mp_ptr nn_t
#define mp_size_t len_t
#define mp_bitcnt_t bits_t
#define mp_srcptr nn_src_t
#define mpz_ptr zz_ptr
#define mpz_t zz_t

#define _mp_d n
#define _mp_size size

#define mpz_init zz_init
#define mpz_clear zz_clear
#define mpz_size(x) (BSDNT_ABS((x)->size))
#define mpz_sgn(x) ((x)->size > 0 ? 1 : ((x)->size < 0 ? -1 : 0))
#define mpn_add nn_add
#define mpn_add_1 nn_add1
#define mpn_sub nn_sub
#define mpn_sub_1 nn_sub1
#define mpn_sub_n nn_sub_m
#define mpz_neg zz_neg
#define mpn_mul nn_mul
#define mpn_mul_1 nn_mul1
#define mpn_mul_n nn_mul_m
#define mpz_divexact zz_div
#define mpn_lshift nn_shl
#define mpn_rshift nn_shr
#define mpn_popcount nn_popcount
#define mpn_hamdist nn_hamdist_m
#define mpn_scan1(a, b) (nn_scan1((b), (a), LEN_MAX))
#define mpn_cmp nn_cmp_m
#define mpz_odd_p zz_odd_p
#define mpn_set_str nn_set_str_raw
#define mpn_get_str nn_get_str_raw
#define mpz_pow_ui zz_powi
#define mpn_gcd nn_gcd

static inline void mpz_realloc2(mpz_t x, mp_bitcnt_t n)
{
  zz_fit(x, !n ? 1 : (n+WORD_BITS-1)/WORD_BITS);
}

static inline void mpn_sqr (mp_limb_t *r, const mp_limb_t *a, mp_size_t n)
{
  mpn_mul(r, a, n, a, n);
}

static inline void mpn_tdiv_qr(mp_limb_t *qp, mp_limb_t *rp, mp_size_t qxn,
                               const mp_limb_t *np, mp_size_t nn,
                               const mp_limb_t *dp, mp_size_t dn)
{
  (void)qxn; /* GMP says this must be 0 */
  if(rp != np)
    memcpy(rp, np, nn*sizeof(mp_limb_t));
  nn_divrem(qp, rp, nn, dp, dn);
}

static inline mp_size_t mpn_gcdext(mp_limb_t *gp,
                                   mp_limb_t *sp, mp_size_t *sn,
                                   mp_limb_t *up, mp_size_t un,
                                   mp_limb_t *vp, mp_size_t vn)
{
  *sn = un;
  return nn_xgcd(gp, sp, up, un, vp, vn);
}

#define mpn_sqrtrem(s, r, p, n) (caml_failwith("Z: sqrtrem unavailable in BSDNT"), 1)
#define mpz_powm(x, y, z, w) ((void)x, (void)y, (void)z, (void)w, caml_failwith("Z: powm unavailable in BSDNT"))
#define mpz_invert(x, y, z) ((void)x, (void)y, (void)z, caml_failwith("Z: invert unavailable in BSDNT"), 0)
#define mpz_root(x, y, z) ((void)x, (void)y, (void)z, caml_failwith("Z: root unavailable in BSDNT"), 0)
#define mpz_perfect_power_p(x) ((void)x, caml_failwith("Z: perfect_power unavailable in BSDNT"), 0)
#define mpz_perfect_square_p(x) ((void)x, caml_failwith("Z: perfect_square unavailable in BSDNT"), 0)
#define mpz_probab_prime_p(x, y) ((void)x, (void)y, caml_failwith("Z: probab_prime_p unavailable in BSDNT"), 0)
#define mpz_nextprime(x, y) ((void)x, (void)y, caml_failwith("Z: nextprime unavailable in BSDNT"))
