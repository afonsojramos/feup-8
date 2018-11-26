@extends('layouts.app')

@section('content')

<button data-toggle="collapse" data-target={{ "test" . $testID }}>Add/edit hint</button>

<div id={{ "test" . $testID }} class="collapse">
    <div class="container">
        <form id={{ "form" . $testID }} class="form-hint">
            <div class="row">
            <input type="hidden" name="testID" value={{ $testID }}>
            <textarea class="col-md-2" name="hint" placeholder="Enter the hint here" >{{ $hint }}</textarea>
            </div>
            <div class="row">
            <button class="hint-submit" type="submit" class="col-md-2 btn btn-success green"><i class="fa fa-share"></i>Add hint</button>
            </div>
        </form>
    </div>
</div>

@endsection
