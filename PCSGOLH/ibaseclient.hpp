#include "vmt.hpp"

struct RecvTable;

struct RecvProp
{
	char					*m_pVarName;
	int						m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;
	bool					m_bInsideArray;
	const void				*m_pExtraData;
	RecvProp				*m_pArrayProp;
	void*					m_ArrayLengthProxy;
	void*					m_ProxyFn;
	void*					m_DataTableProxyFn;
	RecvTable				*m_pDataTable;
	int						m_Offset;
	int						m_ElementStride;
	int						m_nElements;
	const char				*m_pParentArrayPropName;
};

class ClientClass
{
public:
	void*			m_pCreateFn;
	void*			m_pCreateEventFn;
	char			*m_pNetworkName;
	RecvTable		*m_pRecvTable;
	ClientClass		*m_pNext;
	int				m_ClassID;
};

class IBaseClient
{
public:
	ClientClass* GetAllClasses(void)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return callClass<OriginalFn>(this, 8)(this);
	}
};