/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
 *  Main authors:
 *     Jip J. Dekker <jip.dekker@monash.edu>
 *     Guido Tack <guido.tack@monash.edu>
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include <unordered_map>
#include <unordered_set>

#include <minizinc/ast.hh>
#include <minizinc/aststring.hh>

namespace MiniZinc {


  /// Hash map from strings to \a T
  /// Note: This map is only safe to use if the keys are guaranteed to be
  /// marked alive. (For example if they are used in a Model object)
  template <typename T>
  using ASTStringMap = std::unordered_map<ASTString, T>;
  /// Hash set of strings
  /// Note: This set is only safe to use if the keys are guaranteed to be
  /// marked alive. (For example if they are used in a Model object)
  using ASTStringSet = std::unordered_set<ASTString>;

  /// Hash map from strings to \a T
  /// Note: This map will ensure its keys stay alive while it still exists
  /// Specialisations for Expression* and VarDeclI* exist to ensure the
  /// stored values are kept alive as well.
  template<typename T>
  class ManagedASTStringMap : public GCMarker, public std::unordered_map<ASTString, T> {
  protected:
#if defined(MINIZINC_GC_STATS)
    void mark(std::map<int, GCStat>&) override {
#else
    void mark() override {
#endif
      for (auto& it : *this) {
        it.first.mark();
      }
    }
  };


#if defined(MINIZINC_GC_STATS)
  template <>
  void ManagedASTStringMap<Expression*>::mark(std::map<int, GCStat>&);
  template <>
  void ManagedASTStringMap<VarDeclI*>::mark(std::map<int, GCStat>&);
#else
  template <>
  void ManagedASTStringMap<Expression*>::mark();
  template <>
  void ManagedASTStringMap<VarDeclI*>::mark();
#endif

}