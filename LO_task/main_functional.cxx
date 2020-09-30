#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>


#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextTablesSupplier.hpp>
#include <com/sun/star/text/XTextContent.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XTableRows.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTable.hpp>

#include <com/sun/star/frame/Desktop.hpp>


#include <string>
#include <cstdlib>
#include <ctime>
#include <typeinfo>


using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;
using namespace com::sun::star::container;

using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;

#include "main_functional.h"
#include <iostream>

std::string create_name(uint32_t column, uint32_t row) {
    std::string index;
    index += (char) ('A' + column);
    index += std::to_string(row + 1);
    
    return index;
}

void fill_table(Reference <XTextTable> &table, int num_of_col, int num_of_row) {
    for (int x = 0; x < num_of_col; x++) {
        for (int y = 0; y < num_of_row; y++) {
            auto cell = table->getCellByName(OUString::createFromAscii(create_name(x, y).c_str()));
            Reference<XText> cell_text(cell, UNO_QUERY);
            
            std::string cell_value = "row_";
            cell_value += std::to_string(y);
            cell_value += " colm_";
            cell_value += std::to_string(x);
            
            cell_text->setString(OUString::createFromAscii(cell_value.c_str()));
        }
    }
}

void fix_first_row(Reference<XTextTable> &table) {
    auto cell = table->getCellByName(OUString::createFromAscii("A1"));
    Reference<XText> cell_text(cell, UNO_QUERY);
    Reference<XTextRange> text_range(cell_text, UNO_QUERY);
    Reference<XPropertySet> props(text_range, UNO_QUERY);
    

    //auto table_rows = table->getRows();
    //Reference<XIndexAccess> rows(table_rows, UNO_QUERY);
    //Reference<XPropertySet> row_props(rows->getByIndex((short) 0), UNO_QUERY);
    
    auto info = props->getPropertySetInfo();
    auto names = info->getProperties();
    auto size = names.getLength();
    std::cout << size << std::endl;
    for (size_t i = 0; i < size; i++) {
        std::cout << names[i].Name << std::endl;
    }

    /* 
    Any prop;
    prop <<= (sal_Bool) false;
    row_props->setPropertyValue(OUString::createFromAscii("Bold"), prop);
    prop <<= (sal_Bool) true;
    row_props->setPropertyValue(OUString::createFromAscii("AliginLeft"), prop);
*/
}

void create_table(Reference <XMultiServiceFactory> &document, Reference <XText> &text) {
    int num_of_row = std::rand() % 7 + 3;
    int num_of_col = std::rand() % 3 + 3;
    
    Reference <XTextTable> table(document->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
    table->initialize(num_of_row, num_of_col);
    auto text_range = text->getEnd();

    Reference <XTextContent> text_content(table, UNO_QUERY);
    text->insertTextContent(text_range, text_content, (unsigned char) 0);
    fix_first_row(table);

    fill_table(table, num_of_col, num_of_row);
}

void create_new_document(Reference<XComponentContext> xContext){
    Reference<XMultiComponentFactory> xServiceManager = xContext->getServiceManager();
    Reference<XInterface> xDesktop = xServiceManager->createInstanceWithContext(OUString("com.sun.star.frame.Desktop"), xContext);

    Reference<XDesktop2> xDesktop2(xDesktop, UNO_QUERY);

    Reference<XComponent> xComponent = xDesktop2->loadComponentFromURL(OUString("private:factory/swriter"), // URL to the ods file
                                            OUString( "_blank" ), 0,
                                            Sequence < ::com::sun::star::beans::PropertyValue >());
    Reference <XTextDocument> text_document(xComponent, UNO_QUERY);
    Reference <XText> text = text_document->getText();
        
    Reference <XMultiServiceFactory> document(text_document, UNO_QUERY);

    int num_of_tables = 1; //std::rand() % 7 + 2;

    for (int i = 0; i < num_of_tables; i++) {
        auto text_cursor = text->createTextCursor();
        std::string table_name = "\nTable: ";
        table_name += std::to_string(i);

        text_cursor->gotoEnd(false);
        text_cursor->setString(OUString::createFromAscii(table_name.c_str()));
        create_table(document, text);
    }
}



uint32_t get_max_sq_table(Reference<XTextTable> &table) {
    auto cursor = table->createCursorByCellName(OUString::createFromAscii("A1"));
    
    uint32_t columns_count = 1;
    uint32_t rows_count = 1;
    
    while (cursor->goDown(1, false)) columns_count += 1;
    while (cursor->goRight(1, false)) rows_count += 1;

    return columns_count < rows_count ? columns_count : rows_count;
}


void transposite_table(Reference<XTextTable> &table) {
    auto max_sq = get_max_sq_table(table);
    
    for (uint32_t column = 0; column < max_sq; column++) {
        for (uint32_t row = column; row < max_sq; row++) {
            Reference<XCell> fir_cell = table->getCellByName(OUString::createFromAscii(create_name(column, row).c_str()));
            Reference<XCell> sec_cell = table->getCellByName(OUString::createFromAscii(create_name(row, column).c_str()));
            
            Reference<XText> fir_cell_text(fir_cell, UNO_QUERY);
            Reference<XText> sec_cell_text(sec_cell, UNO_QUERY);
        
            auto tmp = fir_cell_text->getString();
            fir_cell_text->setString(sec_cell_text->getString());
            sec_cell_text->setString(tmp);
        }
    }
}


void transposite_all_tables(Reference<XTextDocument> &text_document) {
    Reference<XTextTablesSupplier> table_supplier(text_document, UNO_QUERY);

    auto text_tables = table_supplier->getTextTables();
    
    auto tables_names = text_tables->getElementNames();
    auto size = tables_names.getLength();

    for (size_t i = 0; i < size; i++) {
        Reference<XTextTable> table(text_tables->getByName(tables_names[i]), UNO_QUERY);

        transposite_table(table);
    }
}
