package com.example.caizb.jnicalljava;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by Administrator on 2016/10/30.
 */
public class jnicall {
    Context myctx;

    public jnicall(Context context){
        myctx = context;
    }
    public void jnicallback(String msg, int type){
        Toast.makeText(myctx, msg, Toast.LENGTH_LONG);
    }
    public int jnicallback(String msg, int type){
        Toast.makeText(myctx, msg, Toast.LENGTH_LONG);
        return 0;
    }

    public String jnicallback(String msg, int type){
        Toast.makeText(myctx, msg, Toast.LENGTH_LONG);
        return "0000";
    }

    public void javacalljni(){

    }

    private native int startcalljava();
}
