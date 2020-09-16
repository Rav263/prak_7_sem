#include <stdio.h>
#include <iostream>
#include <wchar.h>

#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>

#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>

#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextContent.hpp>
#include <com/sun/star/table/XCell.hpp>

#include <string>
#include <cstdlib>
#include <ctime>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::text;
using namespace com::sun::star::table;

using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;

void fill_table(Reference <XTextTable> &table, int num_of_col, int num_of_row) {
    for (int x = 0; x < num_of_col; x++) {
        for (int y = 0; y < num_of_row; y++) {
            std::string cell_name;
            cell_name.push_back((char)(x+(int)'A'));
            cell_name.append(std::to_string(y + 1)); 

            auto cell = table->getCellByName(OUString::createFromAscii(cell_name.data()));
            auto text_cursor = Reference<XText>(cell, UNO_QUERY)->createTextCursor();
            
            std::string cell_value = "row_";
            cell_value.append(std::to_string(y));
            cell_value.append(" colm_");
            cell_value.append(std::to_string(x));
            
            text_cursor->setString(OUString::createFromAscii(cell_value.data()));
        }
    }
}

void create_table(Reference <XMultiServiceFactory> &document, Reference <XText> &text) {
    int num_of_row = std::rand() % 7 + 3;
    int num_of_col = std::rand() % 3 + 3;
    
    std::cout << num_of_col << " " << num_of_row << std::endl;

    Reference <XTextTable> table(document->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
    table->initialize(num_of_row, num_of_col);
    auto text_range = text->getEnd();

    Reference <XTextContent> text_content(table, UNO_QUERY);
    text->insertTextContent(text_range, text_content, (unsigned char) 0);

    fill_table(table, num_of_col, num_of_row);
}


SAL_IMPLEMENT_MAIN() {
    std::srand(std::time(nullptr));
    try {
        Reference<XComponentContext> xContext(::cppu::bootstrap());
        if (!xContext.is()) {
            std::cout << std::endl << "Error getting context from running LO instance..." << std::endl;
            return -1;
        }

        // retrieve the service-manager from the context
        Reference<XMultiComponentFactory> xServiceManager = xContext->getServiceManager();
        if (xServiceManager.is())
            std::cout << std::endl << "remote ServiceManager is available" << std::endl;
        else {
            std::cout << std::endl << "remote ServiceManager is not available" << std::endl;
            return 0;
        }
        
        Reference<XInterface> xDesktop = 
            xServiceManager->createInstanceWithContext(OUString("com.sun.star.frame.Desktop"), xContext);

        Reference<XDesktop2> xDesktop2(xDesktop, UNO_QUERY);

        Reference<XComponent> xComponent = 
            xDesktop2->loadComponentFromURL(OUString("private:factory/swriter"), // URL to the ods file
                                            OUString( "_blank" ), 0,
                                            Sequence < ::com::sun::star::beans::PropertyValue >());
        Reference <XTextDocument> text_document(xComponent, UNO_QUERY);
        Reference <XText> text = text_document->getText();
        text->setString(OUString::createFromAscii("Hello, world!"));
        
        Reference <XMultiServiceFactory> document(text_document, UNO_QUERY);

        int num_of_tables = std::rand() % 7 + 2;

        for (int i = 0; i < num_of_tables; i++) {
            auto text_cursor = text->createTextCursor();
            std::string table_name = "\nTable: ";
            table_name.append(std::to_string(i));

            std::cout << table_name << std::endl;
            text_cursor->gotoEnd(false);
            text_cursor->setString(OUString::createFromAscii(table_name.data()));
            create_table(document, text);
        }
    }
    catch (::cppu::BootstrapException& e) {
        fprintf(stderr, "caught BootstrapException: %s\n",
                OUStringToOString( e.getMessage(), RTL_TEXTENCODING_ASCII_US ).getStr());
        return 1;
    }
    catch (Exception& e) {
        fprintf(stderr, "caught UNO exception: %s\n",
                OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US ).getStr());
        return 1;
    }
    return 0;
}
