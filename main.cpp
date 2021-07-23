#include <iostream>

#include <xtensor/xio.hpp>
#include <xtensor/xtensor.hpp>

#include "poisson.h"
#include <ufc.h>

#define NDEBUG

int main() {
  // Rank 0 forms return scalars, rank 1 forms return vectors,
  // Rank 2 forms return matrices.
  const int rank = form_poisson_a->rank;
  std::cout << "Form rank: " << rank << std::endl;

  // The dofmap contains information about the degrees of freedom of the form.
  const std::size_t A_size =
      form_poisson_a->dofmaps[0]->num_element_support_dofs;
  std::cout << "Local cell tensor size: " << A_size << std::endl;

  // Create space to store result of kernel
  xt::xtensor<ufc_scalar_t, 2> A = xt::zeros<double>({A_size, A_size});

  // Create cell geometry information
  const xt::xtensor<double, 2> coordinate_dofs{
      {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};

  // The form has one cell integral
  assert(form_poisson_a->num_integrals(ufc_integral_type::cell) == 1);
  assert(form_poisson_a->num_integrals(ufc_integral_type::interior_facet) == 0);
  assert(form_poisson_a->num_integrals(ufc_integral_type::exterior_facet) == 0);
  // Get the single cell integral
  const ufc_integral *integral =
      form_poisson_a->integrals(ufc_integral_type::cell)[0];

  // This form/integral is very simple, it has no coefficient data, no
  // constants, and it does not require 'permutation' data. What needs to be
  // passed is included in the generated code.
  assert(form_poisson_a->num_coefficients == 0);
  assert(form_poisson_a->num_constants == 0);

  integral->tabulate_tensor(A.data(), nullptr, nullptr, coordinate_dofs.data(),
                            nullptr, nullptr);

  std::cout << A << std::endl;

  return 0;
}
