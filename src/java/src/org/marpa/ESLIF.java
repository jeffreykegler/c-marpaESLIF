/**
 * 
 */
package org.marpa;

import java.nio.ByteBuffer;

/**
 * @author Jean-Damien Durand
 *
 */
public class ESLIF {
	private ESLIFOption _ESLIFOption= null;
	private ByteBuffer  _marpaESLIFp = null;

	private native void jni_init();
	private native void jni_release();
	
	static {
	   System.loadLibrary("marpaESLIF");
	}

	public ESLIF() {
	}
	
	public ESLIF(ESLIFOption ESLIFOption) {
		set_ESLIFOption(ESLIFOption);
	}

	public void init() {
		jni_init(); 
	}
	
	public void release() {
		jni_release();
	}

	private ESLIFOption get_ESLIFOption() {
		return _ESLIFOption;
	}

	private void set_ESLIFOption(ESLIFOption _ESLIFOption) {
		this._ESLIFOption = _ESLIFOption;
	}

	private ByteBuffer get_marpaESLIFp() {
		return _marpaESLIFp;
	}

	private void set_marpaESLIFp(ByteBuffer _marpaESLIFp) {
		this._marpaESLIFp = _marpaESLIFp;
	}

}
