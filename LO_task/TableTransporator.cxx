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

#include <string.h>

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

SAL_IMPLEMENT_MAIN() {
    //OUString sConnectionString(
    //        "uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager");
    try {
        // get the remote office component context
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
        Reference <XTextDocument> xTextDocument(xComponent, UNO_QUERY);
        Reference <XText> xText = xTextDocument->getText();
        xText->setString(OUString::createFromAscii("Hello, world! This is my first table!"));
        
        Reference <XMultiServiceFactory> oDocMSF(xTextDocument, UNO_QUERY);
        Reference <XTextTable> xTable(oDocMSF->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
        xTable->initialize(4, 4);
        auto xTextRange = xText->getEnd();
    
        Reference <XTextContent> xTextContent (xTable, UNO_QUERY);
        xText->insertTextContent(xTextRange, xTextContent, (unsigned char) 0);
        
        Reference <XPropertySet> xTableProps (xTable, UNO_QUERY);
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                std::string cell_name;
                cell_name.push_back((char)(x+(int)'A'));
                cell_name.append(std::to_string(y + 1)); 
                std::cout << cell_name << " ";
                Reference <XCell> xCell = xTable->getCellByName(OUString::createFromAscii(cell_name.data()));
                
                auto x_text_cursor = Reference<XText>(xCell, UNO_QUERY)->createTextCursor();
                
                std::string cell_value = "row_";
                cell_value.append(std::to_string(x));
                cell_value.append(" colm_");
                cell_value.append(std::to_string(y));
                std::cout << cell_value << std::endl;
                x_text_cursor->setString(OUString::createFromAscii(cell_value.data()));
            }
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
