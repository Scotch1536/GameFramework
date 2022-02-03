//!
//!	@file
//!	@brief 数学ライブラリのヘッダーファイル
//!

#pragma once
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

//! @brief 数学ライブラリクラス
static class LCMath
{
public:
	//!
	//! @brief オイラー角からクォータニオンに変換
	//! @param[in] axisX Xの回転軸
	//! @param[in] axisY Yの回転軸
	//! @param[in] axisZ Zの回転軸
	//! @param[in] eulerAngle オイラー角
	//! @param[out] result 結果のクォータニオン
	//! @return const XMFLOAT4& 結果のクォータニオン
	//!
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle , XMFLOAT4& result);

	//!
	//! @brief オイラー角からクォータニオンに変換
	//! @param[in] axisX Xの回転軸
	//! @param[in] axisY Yの回転軸
	//! @param[in] axisZ Zの回転軸
	//! @param[in] eulerAngle オイラー角
	//! @return XMFLOAT4& 結果のクォータニオン
	//!
	static XMFLOAT4 TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle);

	//!
	//! @brief クォータニオンからオイラー角に変換
	//! @param[in] target 変換するクォータニオン
	//! @param[out] result 結果のオイラー角
	//! @return const XMFLOAT3& 結果のオイラー角
	//!
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& target , XMFLOAT3& result);

	//!
	//! @brief クォータニオンからオイラー角に変換
	//! @param[in] target 変換するクォータニオン
	//! @return XMFLOAT3 結果のオイラー角
	//!
	static XMFLOAT3 TransformFromQuaternionToEulerAngles(const XMFLOAT4& target);

	//!
	//! @brief 行列からオイラー角に変換
	//! @param[in] target 変換する行列
	//! @param[out] result 結果のオイラー角
	//! @return const XMFLOAT3& 結果のオイラー角
	//!
	static const XMFLOAT3& TransformFromMatrixToEulerAngles(const XMFLOAT4X4& target , XMFLOAT3& result);

	//!
	//! @brief 行列からオイラー角に変換
	//! @param[in] target 変換する行列
	//! @return XMFLOAT3 結果のオイラー角
	//!
	static XMFLOAT3 TransformFromMatrixToEulerAngles(const XMFLOAT4X4& target);

	//!
	//! @brief クォータニオンを行列に変換
	//! @param[in] target 変換するクォータニオン
	//! @param[out] result 結果の行列
	//! @return const XMFLOAT4X4& 結果の行列
	//!
	static const XMFLOAT4X4& TransformFromQuaternionToMatrix(const XMFLOAT4& target , XMFLOAT4X4& result);

	//!
	//! @brief クォータニオンを行列に変換
	//! @param[in] target 変換するクォータニオン
	//! @return XMFLOAT4X4 結果の行列
	//!
	static XMFLOAT4X4 TransformFromQuaternionToMatrix(const XMFLOAT4& target);

	//!
	//! @brief 単位行列化
	//! @param[in,out] target 単位行列化したい行列,結果の行列
	//!
	static void IdentityMatrix(XMFLOAT4X4& target);

	//!
	//! @brief 単位クォータニオン化
	//! @param[in,out] target 単位クォータニオン化したいクォータニオン,結果のクォータニオン
	//!
	static void IdentityQuaternion(XMFLOAT4& target);

	//!
	//! @brief ロケーション、スケール、回転行列から指定の行列を作成
	//! @param[in] location ロケーション
	//! @param[in] scale スケール
	//! @param[in] rotMTX 回転行列
	//! @param[out] result 結果の行列
	//! @return const XMFLOAT4X4& 結果の行列
	//!
	static const XMFLOAT4X4& CreateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& result);

	//!
	//! @brief ロケーション、スケール、回転行列から指定の行列を作成
	//! @param[in] location ロケーション
	//! @param[in] scale スケール
	//! @param[in] rotMTX 回転行列
	//! @return XMFLOAT4X4 結果の行列
	//!
	static XMFLOAT4X4 CreateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX);

	//!
	//! @brief 逆行列を取得
	//! @param[in] target 逆行列にしたい行列
	//! @param[out] result 結果の行列
	//! @return const XMFLOAT4X4& 結果の行列
	//!
	static const XMFLOAT4X4& InverseMatrix(const XMFLOAT4X4& target , XMFLOAT4X4& result);

	//!
	//! @brief 逆行列を取得
	//! @param[in] target 逆行列にしたい行列
	//! @return XMFLOAT4X4 結果の行列
	//!
	static XMFLOAT4X4 InverseMatrix(const XMFLOAT4X4& target);

	//!
	//! @brief 転置行列を取得
	//! @param[in] target 転置行列にしたい行列
	//! @param[out] result 結果の行列
	//! @return const XMFLOAT4X4& 結果の行列
	//!
	static const XMFLOAT4X4& TransposeMatrix(const XMFLOAT4X4& target , XMFLOAT4X4& result);

	//!
	//! @brief 転置行列を取得
	//! @param[in] target 転置行列にしたい行列
	//! @return XMFLOAT4X4 結果の行列
	//!
	static XMFLOAT4X4 TransposeMatrix(const XMFLOAT4X4& target);

	//!
	//! @brief 指定のFloat3同士が一致しているかの比較
	//! @param[in] target1 比較対象1
	//! @param[in] target2 比較対象2
	//! @return bool 一致しているか
	//!
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief 指定のFloat4同士が一致しているかの比較
	//! @param[in] target1 比較対象1
	//! @param[in] target2 比較対象2
	//! @return bool 一致しているか
	//!
	static bool CompareFloat4(const XMFLOAT4& target1 , const XMFLOAT4& target2);

	//!
	//! @brief 指定の行列同士が一致しているかの比較
	//! @param[in] target1 比較対象1
	//! @param[in] target2 比較対象2
	//! @return bool 一致しているか
	//!
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//!
	//! @brief 軸（向きベクトル）と角度（ラジアン）からクォータニオンを作成
	//! @param[in] axis 軸
	//! @param[in] angleOfRadian 角度
	//! @param[out] result 結果のクォータニオン
	//! @return const XMFLOAT4& 結果のクォータニオン
	//!
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angleOfRadian , XMFLOAT4& result);

	//!
	//! @brief 軸（向きベクトル）と角度（ラジアン）からクォータニオンを作成
	//! @param[in] axis 軸
	//! @param[in] angleOfRadian 角度
	//! @return XMFLOAT4 結果のクォータニオン
	//!
	static XMFLOAT4 CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angleOfRadian);

	//!
	//! @brief クォータニオン同士の乗算
	//! @param[in] target1 乗算する1つ目のクォータニオン
	//! @param[in] target2 乗算する2つ目のクォータニオン
	//! @param[out] result 結果のクォータニオン
	//! @return const XMFLOAT4& 結果のクォータニオン
	//!
	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& target1 , const XMFLOAT4& target2 , XMFLOAT4& result);

	//!
	//! @brief クォータニオン同士の乗算
	//! @param[in] target1 乗算する1つ目のクォータニオン
	//! @param[in] target2 乗算する2つ目のクォータニオン
	//! @return XMFLOAT4 結果のクォータニオン
	//!
	static XMFLOAT4 CalcQuaternionMultiply(const XMFLOAT4& target1 , const XMFLOAT4& target2);


	//!
	//! @brief 行列同士の乗算
	//! @param[in] target1 乗算する1つ目の行列
	//! @param[in] target2 乗算する2つ目の行列
	//! @param[out] result 結果の行列
	//! @return const XMFLOAT4X4& 結果の行列
	//!
	static const XMFLOAT4X4& CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2 , XMFLOAT4X4& result);

	//!
	//! @brief 行列同士の乗算
	//! @param[in] target1 乗算する1つ目の行列
	//! @param[in] target2 乗算する2つ目の行列
	//! @return XMFLOAT4X4 結果の行列
	//!
	static XMFLOAT4X4 CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//!
	//! @brief Float3同士の加算
	//! @param[in] target1 加算する1つ目のFloat3
	//! @param[in] target2 加算する2つ目のFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3Addition(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3同士の加算
	//! @param[in] target1 加算する1つ目のFloat3
	//! @param[in] target2 加算する2つ目のFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3Addition(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3同士の減算
	//! @param[in] target1 減算する1つ目のFloat3
	//! @param[in] target2 減算する2つ目のFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3Subtraction(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3同士の減算
	//! @param[in] target1 減算する1つ目のFloat3
	//! @param[in] target2 減算する2つ目のFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3Subtraction(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief 始点から終点へのベクトルを算出
	//! @details Float3同士の減算とあまり変わらない
	//! @param[in] start 始点のロケーション
	//! @param[in] end 終点のロケーション
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3FromStartToEnd(const XMFLOAT3& start , const XMFLOAT3& end , XMFLOAT3& result);

	//!
	//! @brief 始点から終点へのベクトルを算出
	//! @details Float3同士の減算とあまり変わらない
	//! @param[in] start 始点のロケーション
	//! @param[in] end 終点のロケーション
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3FromStartToEnd(const XMFLOAT3& start , const XMFLOAT3& end);

	//!
	//! @brief Float3の長さを算出
	//! @param[in] target 長さを取得するFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const float& CalcFloat3Length(const XMFLOAT3& target , float& result);

	//!
	//! @brief Float3の長さを算出
	//! @param[in] target 長さを取得するFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static float CalcFloat3Length(const XMFLOAT3& target);

	//!
	//! @brief Float3の正規化したものを算出
	//! @param[in] target 正規化するFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& result);

	//!
	//! @brief Float3の正規化したものを算出
	//! @param[in] target 正規化するFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3Normalize(const XMFLOAT3& target);

	//!
	//! @brief Float3の内積
	//! @param[in] target1 内積する1つ目のFloat3
	//! @param[in] target2 内積する2つ目のFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const float& CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2 , float& result);

	//!
	//! @brief Float3の内積
	//! @param[in] target1 内積する1つ目のFloat3
	//! @param[in] target2 内積する2つ目のFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static float CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3の外積
	//! @param[in] target1 外積する1つ目のFloat3
	//! @param[in] target2 外積する2つ目のFloat3
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3の外積
	//! @param[in] target1 外積する1つ目のFloat3
	//! @param[in] target2 外積する2つ目のFloat3
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3のスカラー積
	//! @param[in] target スカラー積するFloat3
	//! @param[in] scalar スカラー値
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3Scalar(const XMFLOAT3& target , const float& scalar , XMFLOAT3& result);

	//!
	//! @brief Float3のスカラー積
	//! @param[in] target スカラー積するFloat3
	//! @param[in] scalar スカラー値
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3Scalar(const XMFLOAT3& target , const float& scalar);

	//!
	//! @brief Float3を行列と乗算
	//! @param[in] target 乗算するFloat3
	//! @param[in] mtx 乗算する行列
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& CalcFloat3MultplyMatrix(const XMFLOAT3& target , const XMFLOAT4X4& mtx , XMFLOAT3& result);

	//!
	//! @brief Float3を行列と乗算
	//! @param[in] target 乗算するFloat3
	//! @param[in] mtx 乗算する行列
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 CalcFloat3MultplyMatrix(const XMFLOAT3& target , const XMFLOAT4X4& mtx);

	//!
	//! @brief Float3配列から最小最大値を算出
	//! @param[in] target 対象の配列
	//! @param[out] resultMin 結果の最小値
	//! @param[out] resultMax 結果の最大値
	//!
	static const void CalcFloat3MinMax(const std::vector<XMFLOAT3>& target , XMFLOAT3& resultMin , XMFLOAT3& resultMax);

	//!
	//! @brief Floatの線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @param[out] result 結果のFloat
	//! @return const float& 結果のFloat
	//!
	static const float& Lerp(const float& start , const float& end , const float& alpha , float& result);

	//!
	//! @brief Floatの線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @return float 結果のFloat
	//!
	static float Lerp(const float& start , const float& end , const float& alpha);

	//!
	//! @brief Float3の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @param[out] result 結果のFloat3
	//! @return const XMFLOAT3& 結果のFloat3
	//!
	static const XMFLOAT3& Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha , XMFLOAT3& result);

	//!
	//! @brief Float3の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @return XMFLOAT3 結果のFloat3
	//!
	static XMFLOAT3 Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha);

	//!
	//! @brief Float4の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @param[out] result 結果のFloat4
	//! @return const XMFLOAT4& 結果のFloat4
	//!
	static const XMFLOAT4& Lerp(const XMFLOAT4& start , const XMFLOAT4& end , const float& alpha , XMFLOAT4& result);

	//!
	//! @brief Float4の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @return XMFLOAT4 結果のFloat4
	//!
	static XMFLOAT4 Lerp(const XMFLOAT4& start , const XMFLOAT4& end , const float& alpha);

	//!
	//! @brief Float4X4（行列）の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @param[out] result 結果のFloat4X4
	//! @return const XMFLOAT4X4& 結果のFloat4X4
	//!
	static const XMFLOAT4X4& Lerp(const XMFLOAT4X4& start , const XMFLOAT4X4& end , const float& alpha , XMFLOAT4X4& result);

	//!
	//! @brief Float4X4（行列）の線形補間
	//! @param[in] start 開始
	//! @param[in] end 終了
	//! @param[in] alpha アルファ値
	//! @return XMFLOAT4X4 結果のFloat4X4
	//!
	static XMFLOAT4X4 Lerp(const XMFLOAT4X4& start , const XMFLOAT4X4& end , const float& alpha);
};