/*
 * @Author       : PeripateticWind
 * @Email        : zhangzhihong@stu.xjtu.edu.cn
 * @Company      : Xi'an Jiaotong University
 * @CreateTime   : 2020-02-03 16:29:46
 * @Description  : The G2O model's edge implementation file
 * @FilePath     : /2019_nCoV_prediction/2019_nCoV_prediction/include/curve_fitting_edge.h
 * @LastEditors  : PeripateticWind
 * @LastEditTime : 2020-02-06 20:39:22
 * @youwant      : add what you want
 * @Copyright (c) 2020, PeripateticWind. All rights reserved.
 */

#pragma once
// STL
#include <iostream>

// Eigen
#include <Eigen/Core>

// G2O
#include <g2o/core/base_unary_edge.h>

// USER
#include "curve_fitting_vertex.h"

class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /**
     * @brief Construct a new Curve Fitting Edge object
     *
     * @param x 模型自变量x
     */
    CurveFittingEdge(double x)
        : BaseUnaryEdge()
        , _x(x)
    {
    }

    /**
     * @brief 计算曲线模型误差
     *
     */
    virtual void computeError() override  // 本函数提供误差计算模型
    {
        const CurveFittingVertex* vertex           = static_cast<const CurveFittingVertex*>(_vertices[0]);  // 获取顶点
        const Eigen::Vector3d     vertexEstimation = vertex->estimate();                                    // 获取估计值

        _error(0, 0) = _measurement - vertexEstimation(0, 0) * vertexEstimation(1, 0) / (vertexEstimation(1, 0) + (vertexEstimation(0, 0) - vertexEstimation(1, 0)) * std::exp(-vertexEstimation(2, 0) * _x));  // 计算误差值 _measurement为观测值,
    }

    // 存盘和读盘:留空
    virtual bool read(std::istream& in) override {}
    virtual bool write(std::ostream& out) const override {}

public:
    double _x;  // x的值 y的值为_measurement
};
