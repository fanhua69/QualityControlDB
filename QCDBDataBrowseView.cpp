// DataBrowseView.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "qcdbdatabrowsedoc.h"
#include "qcdbdatabrowseview.h"
#include "FHCGlobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// CQCDBDataBrowseView

IMPLEMENT_DYNCREATE(CQCDBDataBrowseView, CDataBrowseView)

CQCDBDataBrowseView::CQCDBDataBrowseView()
{
}

CQCDBDataBrowseView::~CQCDBDataBrowseView()
{
}

BEGIN_MESSAGE_MAP(CQCDBDataBrowseView, CDataBrowseView)
    ON_COMMAND(ID_DBBROWSE_InputQCData, OnDbbrowseInputqcdata)
    ON_UPDATE_COMMAND_UI(ID_DBBROWSE_InputQCData, OnUpdateDbbrowseInputqcdata)
END_MESSAGE_MAP()



// CQCDBDataBrowseView diagnostics

#ifdef _DEBUG
void CQCDBDataBrowseView::AssertValid() const
{
	CDataBrowseView::AssertValid();
}

void CQCDBDataBrowseView::Dump(CDumpContext& dc) const
{
	CDataBrowseView::Dump(dc);
}
#endif //_DEBUG


void  CQCDBDataBrowseView::SetComboxContents(   CString         sTableName,
                                                CFieldData      *pFields,
                                                int             iFieldQty,
                                                int             iFixedRowOrColQty, 
                                                bool            bSetRowToCol)
{
    int i=0,j=0;
    CString sField;
    CStringArray &arrayMonitorNames     =GetMonitorNames();
    CStringArray &arrayProjectNames     =GetProjectNames();
    CStringArray &arrayTechnicianNames  =GetTechnicianNames();
    CStringArray &arrayInstNames        =GetInstrumentNames();
    CStringArray &arrayLineNames        =GetSurveyLines();

    m_Grid.RemoveAllCombos();

    int iProjectFieldOrder=-1;
    int iLineFieldOrder=-1;
    for(i=0;i<iFieldQty;i++)
    {
        sField=pFields[i].sFieldName;
        if(sField.Find("��Ŀ���")!=-1)
        {
            if(bSetRowToCol)
            {
                m_Grid.SetComboContent(iFixedRowOrColQty+i,-1,arrayProjectNames);
            }
            else
            {
                m_Grid.SetComboContent(-1,iFixedRowOrColQty+i,arrayProjectNames);
            }
            iProjectFieldOrder=i;
        }

        if(     sField=="�ල����"
            ||  sField=="פ�Ӽල"
            ||  sField=="�����ල"
            ||  sField=="�����" 
            ||  sField=="פ�Ӽලǩ��"
            ||  sField=="ִ�о���"           
            ||  sField=="̽��ִ�о���"            
            ||  sField=="�ֳ��ල")
        {
            if(bSetRowToCol)
            {
                m_Grid.SetComboContent(iFixedRowOrColQty+i,-1,arrayMonitorNames);
            }
            else
            {
                m_Grid.SetComboContent(-1,iFixedRowOrColQty+i,arrayMonitorNames);
            }
        }

        else if(    sField=="������Ա����"
                ||  sField=="��ͬ�����"
                ||  sField=="��ͬ��"
                ||  sField=="ʩ����λ�쵼ǩ��")
        {
            if(bSetRowToCol)
            {
                m_Grid.SetComboContent(iFixedRowOrColQty+i,-1,arrayTechnicianNames);
            }
            else
            {
                m_Grid.SetComboContent(-1,iFixedRowOrColQty+i,arrayTechnicianNames);
            }
        }

        else if(sField.Find("�����ͺ�")!=-1)
        {
            if(bSetRowToCol)
            {
                m_Grid.SetComboContent(iFixedRowOrColQty+i,-1,arrayInstNames);
            }
            else
            {
                m_Grid.SetComboContent(-1,iFixedRowOrColQty+i,arrayInstNames);
            }
        }

        else if(sField.Find("���߱��")!=-1)
        {
            if(bSetRowToCol)
            {
                for(j=iFixedRowOrColQty;j<m_Grid.GetColumnCount();j++)
                {
                    m_Grid.SetComboContent(iFixedRowOrColQty+i,j,arrayLineNames);
                }
            }
            else
            {
                for(j=iFixedRowOrColQty;j<m_Grid.GetRowCount();j++)
                {
                    m_Grid.SetComboContent(j,iFixedRowOrColQty+i,arrayLineNames);
                }
            }
            iLineFieldOrder=i;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Set the line name combos according to the project name:
    ////////////////////////////////////////////////////////////////////////////
    if(iProjectFieldOrder!=-1&&iLineFieldOrder!=-1)
    {
        CString sProjectName;
        if(bSetRowToCol)
        {
            for(i=iFixedRowOrColQty;i<m_Grid.GetColumnCount();i++)
            {
                GetItem(iProjectFieldOrder+2,i,sProjectName);
                ComboModified(iProjectFieldOrder+2,i,sProjectName);
            }
        }
        else
        {
            for(i=iFixedRowOrColQty;i<m_Grid.GetRowCount();i++)
            {
                GetItem(i,iProjectFieldOrder+2,sProjectName);
                ComboModified(i,iProjectFieldOrder+2,sProjectName);
            }
        }
    }
}


void CQCDBDataBrowseView::OnUpdatedb()
{
    CDataBrowseView::OnUpdatedb();
}

void CQCDBDataBrowseView::OnUpdateDbbrowseInputqcdata(CCmdUI *pCmdUI)
{
	CDataBrowseDoc *pDoc=(CDataBrowseDoc *)GetDocument();
	CString sTable=pDoc->GetTableName ();
	sTable=sTable.Left (4);
	pCmdUI->Enable (sTable=="��10");
}

void CQCDBDataBrowseView::OnDbbrowseInputqcdata()
{
    CQCDBDataBrowseDoc *pDoc=(CQCDBDataBrowseDoc *)GetDocument();
    pDoc->InputQCData();
}

void CQCDBDataBrowseView::ComboModified(int iRow,int iCol,CString sNewName)
{
    CDataBrowseDoc *pDoc=(CDataBrowseDoc *)GetDocument();
    CString sTable=pDoc->GetTableName ();

    int iDelayField=0; // the field quantity between "survey line" and "project" 
    if(     sTable=="��0301�������ձ�"
        ||  sTable=="��0302�����ල�ձ�"
        ||  sTable=="��0403ԭʼ��¼�ල���������ļ��ǼǱ�"
        ||  sTable=="��1002SPS�첨���ܽ�"
        ||  sTable=="��1004SPS�ڵ��ܽ�"
        ||  sTable=="��1007���ڷ�Ƶ�����ܽ�"
        ||  sTable=="��1009�������������ܽ�"
        ||  sTable=="��1011�첨�������������"
        ||  sTable=="��1013�첨�������ܽ�"
        ||  sTable=="��1013�첨�������ܽ�")
    {
        iDelayField=1;
    }
    else if(sTable=="��0402�ල��鱸��¼")
    {
        iDelayField=2;
    }

    if(iDelayField!=0)
    {
        CStringArray array;
        GetSurveyLinesOfProject(sNewName,array);
        if(array.GetCount()==0)
        {
            CStringArray &a=GetSurveyLines();
            array.Append(a);
        }

        if(IsVerticalView())
        {
            m_Grid.SetComboContent(iRow+iDelayField,iCol,array);
        }
        else
        {
            m_Grid.SetComboContent(iRow,iCol+iDelayField,array);
        }
    }
}