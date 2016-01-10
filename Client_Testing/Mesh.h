#ifndef MESH_H_
#define MESH_H_



/*메쉬의 베이스 추상 클래스*/
class CMesh
{
public:
	//CMesh 클래스의 생성자와 소멸자를 선언한다. 
	CMesh(ID3D11Device *pd3dDevice);
	virtual ~CMesh();

	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);	// 정점 데이터를 렌더링한다

	void AddRef();
	void Release();

protected:
	ID3D11Buffer *m_pd3dVertexBuffer;	/* 정점 버퍼 인터페이스 포인터. 정점 데이터 저장용 */
	UINT m_nVertices;	// 정점 버퍼의 정점 개수
	UINT m_nStride;		// 정점 하나의 바이트 수
	UINT m_nOffset;		// 정점의 데이터가 정점 버퍼의 어디서 시작하는가
	D3D11_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology;	/* 어떤 프리미티브 형태로 정점 데이터를 조립해야 하는가*/


	ID3D11Buffer *m_pd3dIndexBuffer;	/* 인덱스 버퍼 인터페이스 포인터. 인덱스 데이터 저장용*/
	UINT m_nIndices;	// 인덱스 버퍼의 인덱스 개수
	UINT m_nStartIndex;	// 어느 인덱스부터 사용하여 정점을 조립할 것인가
	int m_nBaseVertex;	// 각 인덱스에 더해질 인덱스

	ID3D11RasterizerState *m_pd3dRasterizerState;	// 래스터라이저 상태 객체에 대한 인터페이스 포인터
	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);	// 래스터라이저 상태를 생성한다

private:
	int m_nReferences;	// 이 메쉬가 참조하고 있는 객체수
};





/* 조명의 영향을 받는 메쉬의 베이스 클래스 */
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshIlluminated();

	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);

protected:
	void CalculateVertexNormal(BYTE *pVertices, WORD *pIndices); /* 정점의 법선 벡터를 계산. 정점 데이터와 인덱스 데이터를 사용 */

private:
	void SetTriAngleListVertexNormal(BYTE *pVertices); /* '인덱스 버퍼를 사용하지 않는' 삼각형 리스트에 대해 법선 벡터 계산 */
	void SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip); /* '인덱스 버퍼를 사용하는' 경우 프리미티브 순서와 관계 없이, 그 정점을 포함하는 삼각형의 법선 벡터들의 평균으로 계산 */

	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2); /* 삼각형의 세 정점을 사용하여 삼각형의 법선 벡터를 계산 */
};





class CCubeMeshIlluminatedTextured : public CMeshIlluminated
{
public:
	CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshIlluminatedTextured();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};



#endif