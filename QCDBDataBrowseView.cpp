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
        if(sField.Find("项目编号")!=-1)
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

        if(     sField=="监督姓名"
            ||  sField=="驻队监督"
            ||  sField=="测量监督"
            ||  sField=="检查人" 
            ||  sField=="驻队监督签字"
            ||  sField=="执行经理"           
            ||  sField=="探区执行经理"            
            ||  sField=="现场监督")
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

        else if(    sField=="技术人员姓名"
                ||  sField=="陪同检查人"
                ||  sField=="陪同人"
                ||  sField=="施工单位领导签字")
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

        else if(sField.Find("仪器型号")!=-1)
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

        else if(sField.Find("测线编号")!=-1)
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
	pCmdUI->Enable (sTable=="表10");
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
    if(     sTable=="表0301监理工作日报"
        ||  sTable=="表0302测量监督日报"
        ||  sTable=="表0403原始记录监督复评降级文件登记表"
        ||  sTable=="表1002SPS检波点总结"
        ||  sTable=="表1004SPS炮点总结"
        ||  sTable=="表1007单炮分频能量总结"
        ||  sTable=="表1009单炮整体能量总结"
        ||  sTable=="表1011检波器测试情况资料"
        ||  sTable=="表1013检波器测试总结"
        ||  sTable=="表1013检波器测试总结")
    {
        iDelayField=1;
    }
    else if(sTable=="表0402监督检查备忘录")
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