#include "transpositor.hxx"

#include <iostream>


#include <com/sun/star/task/XJobListener.hpp>

#include <com/sun/star/ui/ContextMenuInterceptorAction.hpp>
#include <com/sun/star/ui/XContextMenuInterception.hpp>
#include <com/sun/star/ui/ContextMenuExecuteEvent.hpp>
#include <com/sun/star/ui/ActionTriggerSeparatorType.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>


using namespace com::sun::star::ui;
using namespace com::sun::star::uno;

ContextMenuInterceptorAction SAL_CALL TableTranspositor::execuation(const ContextMenuExecuteEvent& rEvent) 
    throw (RuntimeException) {
    /*

    try {
	    Reference<XIndexContainer> xContextMenu = rEvent.ActionTriggerContainer;
	    
        if (!xContextMenu.is()) {
	        return ContextMenuInterceptorAction_IGNORED;
	    }
	
        Reference<XMultiServiceFactory> xMenuElementFactory(xContextMenu, UNO_QUERY);
	
        if (!xMenuElementFactory.is()) {
	        return ContextMenuInterceptorAction_IGNORED;
	    }

	    Reference<XPropertySet> xSeparator(xMenuElementFactory->createInstance("com.sun.star.ui.ActionTriggerSeparator"), UNO_QUERY);
	
        if (!xSeparator.is()) {
	        return ContextMenuInterceptorAction_IGNORED;
        }

	    xSeparator->setPropertyValue("SeparatorType", makeAny(ActionTriggerSeparatorType::LINE));
	
	    Reference<XPropertySet> xMenuEntry(xMenuElementFactory->createInstance("com.sun.star.ui.ActionTrigger"), UNO_QUERY );
	
        if (!xMenuEntry.is()) {
	        return ContextMenuInterceptorAction_IGNORED;
	    }

	    xMenuEntry->setPropertyValue("Text", makeAny(OUString("Search")));
	    xMenuEntry->setPropertyValue("CommandURL", makeAny(OUString("vnd.sun.star.job:event=onIncrementClick")));

	    sal_Int32 nCount = xContextMenu->getCount();
	    sal_Int32 nIdx = nCount;
	    xContextMenu->insertByIndex(nIdx++, makeAny( xSeparator));
	    xContextMenu->insertByIndex(nIdx++, makeAny( xMenuEntry));

	    return ContextMenuInterceptorAction_CONTINUE_MODIFIED;
    } catch (Exception& e){}
    */
    std::cout << "YOU CLICK ON THE FUCKING BUTTON" << std::endl;
    return ContextMenuInterceptorAction_IGNORED;
}
