#pragma once

#include <iostream>
#include <unordered_map>

#include "mtr.h"

using MatMulFunc = Matrix(*) (const Matrix &, const Matrix &);

namespace Multiply
{
    Matrix classicAlg(const Matrix &m1, const Matrix &m2);
    Matrix winograd(const Matrix &mtrx, const Matrix &mtry);
    Matrix winogradOpt(const Matrix &mtrx, const Matrix &mtry);
    Matrix strassenAlg(const Matrix &mtrx, const Matrix &mtry);
};
