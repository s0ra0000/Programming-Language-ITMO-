%define START_ELEMENT 0
%macro colon 2

    %ifid %2
        %2: dq START_ELEMENT
        %define START_ELEMENT %2
    %else
        %fatal "Second argument: нужен идентификатор!"
    %endif

    %ifstr %1
        db %1, 0
    %else   
        %fatal "First argument: Ключом должен быть string!"
    %endif
%endmacro


